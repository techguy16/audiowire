/* WirePlumber
 *
 * Copyright © 2020 Collabora Ltd.
 *    @author Julian Bouzas <julian.bouzas@collabora.com>
 *
 * SPDX-License-Identifier: MIT
 */

#define G_LOG_DOMAIN "wp-iterator"

#include "iterator.h"
#include <spa/utils/defs.h>

struct _WpIterator
{
  const WpIteratorMethods *methods;
  gpointer user_data;
};

G_DEFINE_BOXED_TYPE (WpIterator, wp_iterator, wp_iterator_ref, wp_iterator_unref)

static gboolean
wp_iterator_default_fold (WpIterator *self, WpIteratorFoldFunc func,
    GValue *item, gpointer data)
{
  GValue next = G_VALUE_INIT;

  wp_iterator_reset (self);

  while (wp_iterator_next (self, &next)) {
    const gboolean res = func (&next, item, data);
    g_value_unset (&next);
    if (!res)
      return FALSE;
  }

  return TRUE;
}

struct foreach_fold_data {
  WpIteratorForeachFunc func;
  gpointer data;
};

static gboolean
foreach_fold_func (const GValue *item, GValue *ret, gpointer data)
{
  struct foreach_fold_data *d = data;
  d->func (item, d->data);
  return TRUE;
}

static gboolean
wp_iterator_default_foreach (WpIterator *self, WpIteratorForeachFunc func,
   gpointer data)
{
  struct foreach_fold_data d = {func, data};
  return wp_iterator_fold (self, foreach_fold_func, NULL, &d);
}

/**
 * wp_iterator_new:
 * @methods: method implementations for the new iterator
 * @user_size: size of the user_data structure to be allocated
 *
 * Constructs an iterator that uses the provided @methods to implement its API.
 * The WpIterator structure is internally allocated with @user_size additional
 * space at the end. A pointer to this space can be retrieved with
 * wp_iterator_get_user_data() and is available for implementation-specific
 * storage.
 *
 * Returns: (transfer full): a new custom iterator
 */
WpIterator *
wp_iterator_new (const WpIteratorMethods *methods, size_t user_size)
{
  WpIterator *self = NULL;

  g_return_val_if_fail (methods, NULL);

  self = g_rc_box_alloc0 (sizeof (WpIterator) + user_size);
  self->methods = methods;
  if (user_size > 0)
    self->user_data = SPA_MEMBER (self, sizeof (WpIterator), void);

  return self;
}

/**
 * wp_iterator_get_user_data:
 * @self: an iterator object
 *
 * Note: this only for use by implementations of WpIterator
 *
 * Returns: a pointer to the implementation-specific storage area
 */
gpointer
wp_iterator_get_user_data (WpIterator *self)
{
  return self->user_data;
}

/**
 * wp_iterator_ref:
 * @self: an iterator object
 *
 * Returns: (transfer full): @self with an additional reference count on it
 */
WpIterator *
wp_iterator_ref (WpIterator *self)
{
  return (WpIterator *) g_rc_box_acquire ((gpointer) self);
}

static void
wp_iterator_free (WpIterator *self)
{
  if (self->methods->finalize)
    self->methods->finalize (self);
}

/**
 * wp_iterator_unref:
 * @self: (transfer full): an iterator object
 *
 * Decreases the reference count on @self and frees it when the ref count
 * reaches zero.
 */
void
wp_iterator_unref (WpIterator *self)
{
  g_rc_box_release_full (self, (GDestroyNotify) wp_iterator_free);
}

/**
 * wp_iterator_reset:
 * @self: the iterator
 *
 * Resets the iterator so we can iterate again from the beginning.
 */
void
wp_iterator_reset (WpIterator *self)
{
  g_return_if_fail (self);
  g_return_if_fail (self->methods->reset);

  self->methods->reset (self);
}

/**
 * wp_iterator_next:
 * @self: the iterator
 * @item: (out): the next item of the iterator
 *
 * Gets the next item of the iterator.
 *
 * Returns: TRUE if next iterator was obtained, FALSE when the iterator has no
 * more items to iterate through.
 */
gboolean
wp_iterator_next (WpIterator *self, GValue *item)
{
  g_return_val_if_fail (self, FALSE);
  g_return_val_if_fail (self->methods->next, FALSE);

  return self->methods->next (self, item);
}

/**
 * wp_iterator_fold:
 * @self: the iterator
 * @func: (scope call): the fold function
 * @ret: (inout): the accumulator data
 * @data: (closure): the user data
 *
 * Iterates over all items of the iterator calling a function.
 *
 * Returns: TRUE if all the items were processed, FALSE otherwise.
 */
gboolean
wp_iterator_fold (WpIterator *self, WpIteratorFoldFunc func, GValue *ret,
    gpointer data)
{
  g_return_val_if_fail (self, FALSE);

  if (self->methods->fold)
    return self->methods->fold (self, func, ret, data);

  return wp_iterator_default_fold (self, func, ret, data);
}

/**
 * wp_iterator_foreach:
 * @self: the iterator
 * @func: (scope call): the foreach function
 * @data: (closure): the user data
 *
 * Fold a function over the items of the iterator.
 *
 * Returns: TRUE if all the items were processed, FALSE otherwise.
 */
gboolean
wp_iterator_foreach (WpIterator *self, WpIteratorForeachFunc func,
   gpointer data)
{
  g_return_val_if_fail (self, FALSE);

  if (self->methods->foreach)
    return self->methods->foreach (self, func, data);

  return wp_iterator_default_foreach (self, func, data);
}

struct ptr_array_iterator_data
{
  GPtrArray *array;
  GType item_type;
  guint index;
  void (*set_value) (GValue *, gpointer);
};

static void
ptr_array_iterator_reset (WpIterator *it)
{
  struct ptr_array_iterator_data *it_data = wp_iterator_get_user_data (it);
  it_data->index = 0;
}

static gboolean
ptr_array_iterator_next (WpIterator *it, GValue *item)
{
  struct ptr_array_iterator_data *it_data = wp_iterator_get_user_data (it);

  if (it_data->index < it_data->array->len) {
    gpointer ptr = g_ptr_array_index (it_data->array, it_data->index++);
    g_value_init (item, it_data->item_type);
    it_data->set_value (item, ptr);
    return TRUE;
  }
  return FALSE;
}

static gboolean
ptr_array_iterator_fold (WpIterator *it, WpIteratorFoldFunc func, GValue *ret,
    gpointer data)
{
  struct ptr_array_iterator_data *it_data = wp_iterator_get_user_data (it);
  gpointer *ptr, *base;
  guint len;

  ptr = base = it_data->array->pdata;
  len = it_data->array->len;

  while ((ptr - base) < len) {
    g_auto (GValue) item = G_VALUE_INIT;
    g_value_init (&item, it_data->item_type);
    it_data->set_value (&item, *ptr);
    if (!func (&item, ret, data))
      return FALSE;
    ptr++;
  }
  return TRUE;
}

static void
ptr_array_iterator_finalize (WpIterator *it)
{
  struct ptr_array_iterator_data *it_data = wp_iterator_get_user_data (it);
  g_ptr_array_unref (it_data->array);
}

static const WpIteratorMethods ptr_array_iterator_methods = {
  .reset = ptr_array_iterator_reset,
  .next = ptr_array_iterator_next,
  .fold = ptr_array_iterator_fold,
  .finalize = ptr_array_iterator_finalize,
};

/**
 * wp_iterator_new_ptr_array:
 * @items: (transfer full): the items to iterate over
 * @item_type: the type of each item
 *
 * Returns: (transfer full): a new iterator that iterates over @items
 */
WpIterator *
wp_iterator_new_ptr_array (GPtrArray * items, GType item_type)
{
  g_autoptr (WpIterator) it = NULL;
  struct ptr_array_iterator_data *it_data;

  g_return_val_if_fail (items != NULL, NULL);

  it = wp_iterator_new (&ptr_array_iterator_methods,
      sizeof (struct ptr_array_iterator_data));
  it_data = wp_iterator_get_user_data (it);
  it_data->array = items;
  it_data->item_type = item_type;
  it_data->index = 0;

  if (g_type_is_a (item_type, G_TYPE_POINTER))
    it_data->set_value = g_value_set_pointer;
  else if (g_type_is_a (item_type, G_TYPE_BOXED))
    it_data->set_value = (void (*) (GValue *, gpointer)) g_value_set_boxed;
  else if (g_type_is_a (item_type, G_TYPE_OBJECT))
    it_data->set_value = g_value_set_object;
  else if (g_type_is_a (item_type, G_TYPE_INTERFACE))
    it_data->set_value = g_value_set_object;
  else if (g_type_is_a (item_type, G_TYPE_VARIANT))
    it_data->set_value = (void (*) (GValue *, gpointer)) g_value_set_variant;
  else if (g_type_is_a (item_type, G_TYPE_STRING))
    it_data->set_value = (void (*) (GValue *, gpointer)) g_value_set_string;
  else
    g_return_val_if_reached (NULL);

  return g_steal_pointer (&it);
}
