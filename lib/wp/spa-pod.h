/* WirePlumber
 *
 * Copyright © 2020 Collabora Ltd.
 *    @author Julian Bouzas <julian.bouzas@collabora.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __WIREPLUMBER_SPA_POD_H__
#define __WIREPLUMBER_SPA_POD_H__

#include <gio/gio.h>

#include "defs.h"
#include "iterator.h"

G_BEGIN_DECLS

/**
 * WP_TYPE_SPA_POD:
 *
 * The #WpSpaPod #GType
 */
#define WP_TYPE_SPA_POD (wp_spa_pod_get_type ())
WP_API
GType wp_spa_pod_get_type (void);

typedef struct _WpSpaPod WpSpaPod;

WP_API
WpSpaPod *wp_spa_pod_ref (WpSpaPod *self);

WP_API
void wp_spa_pod_unref (WpSpaPod *self);

WP_API
const char *wp_spa_pod_get_type_name (const WpSpaPod *self);

WP_API
const char *wp_spa_pod_get_choice_type_name (const WpSpaPod *self);

WP_API
const char *wp_spa_pod_get_object_type_name (const WpSpaPod *self);

WP_API
WpSpaPod *wp_spa_pod_copy (const WpSpaPod *other);

WP_API
gboolean wp_spa_pod_is_unique_owner ( WpSpaPod *self);

WP_API
WpSpaPod *wp_spa_pod_ensure_unique_owner (WpSpaPod *self);

WP_API
WpSpaPod *wp_spa_pod_new_none (void);

WP_API
WpSpaPod *wp_spa_pod_new_boolean (gboolean value);

WP_API
WpSpaPod *wp_spa_pod_new_id (guint32 value);

WP_API
WpSpaPod *wp_spa_pod_new_int (gint value);

WP_API
WpSpaPod *wp_spa_pod_new_long (glong value);

WP_API
WpSpaPod *wp_spa_pod_new_float (float value);

WP_API
WpSpaPod *wp_spa_pod_new_double (double value);

WP_API
WpSpaPod *wp_spa_pod_new_string (const char *value);

WP_API
WpSpaPod *wp_spa_pod_new_bytes (gconstpointer value, guint32 len);

WP_API
WpSpaPod *wp_spa_pod_new_pointer (const char *type_name, gconstpointer value);

WP_API
WpSpaPod *wp_spa_pod_new_fd (gint64 value);

WP_API
WpSpaPod *wp_spa_pod_new_rectangle (guint32 width, guint32 height);

WP_API
WpSpaPod *wp_spa_pod_new_fraction (guint32 num, guint32 denom);

WP_API
WpSpaPod *wp_spa_pod_new_choice (const char *type_name, ...)
    G_GNUC_NULL_TERMINATED;

WP_API
WpSpaPod *wp_spa_pod_new_choice_valist (const char *type_name, va_list args);

WP_API
WpSpaPod *wp_spa_pod_new_object (const char *type_name, const char *id_name,
    ...) G_GNUC_NULL_TERMINATED;

WP_API
WpSpaPod *wp_spa_pod_new_object_valist (const char *type_name,
    const char *id_name, va_list args);

WP_API
WpSpaPod *wp_spa_pod_new_sequence (guint unit, ...) G_GNUC_NULL_TERMINATED;

WP_API
WpSpaPod *wp_spa_pod_new_sequence_valist (guint unit, va_list args);

WP_API
gboolean wp_spa_pod_is_none (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_boolean (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_id (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_int (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_long (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_float (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_double (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_string (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_bytes (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_pointer (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_fd (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_rectangle (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_fraction (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_array (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_choice (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_object (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_struct (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_sequence (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_property (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_is_control (const WpSpaPod *self);

WP_API
gboolean wp_spa_pod_get_boolean (const WpSpaPod *self, gboolean *value);

WP_API
gboolean wp_spa_pod_get_id (const WpSpaPod *self, guint32 *value);

WP_API
gboolean wp_spa_pod_get_int (const WpSpaPod *self, gint *value);

WP_API
gboolean wp_spa_pod_get_long (const WpSpaPod *self, glong *value);

WP_API
gboolean wp_spa_pod_get_float (const WpSpaPod *self, float *value);

WP_API
gboolean wp_spa_pod_get_double (const WpSpaPod *self, double *value);

WP_API
gboolean wp_spa_pod_get_string (const WpSpaPod *self, const char **value);

WP_API
gboolean wp_spa_pod_get_bytes (const WpSpaPod *self, gconstpointer *value,
    guint32 *len);

WP_API
gboolean wp_spa_pod_get_pointer (const WpSpaPod *self, const char **type_name,
   gconstpointer *value);

WP_API
gboolean wp_spa_pod_get_fd (const WpSpaPod *self, gint64 *value);

WP_API
gboolean wp_spa_pod_get_rectangle (const WpSpaPod *self, guint32 *width,
    guint32 *height);

WP_API
gboolean wp_spa_pod_get_fraction (const WpSpaPod *self, guint32 *num,
    guint32 *denom);

WP_API
gboolean wp_spa_pod_set_boolean (WpSpaPod *self, gboolean value);

WP_API
gboolean wp_spa_pod_set_id (WpSpaPod *self, guint32 value);

WP_API
gboolean wp_spa_pod_set_int (WpSpaPod *self, gint value);

WP_API
gboolean wp_spa_pod_set_long (WpSpaPod *self, glong value);

WP_API
gboolean wp_spa_pod_set_float (WpSpaPod *self, float value);

WP_API
gboolean wp_spa_pod_set_double (WpSpaPod *self, double value);

WP_API
gboolean wp_spa_pod_set_pointer (WpSpaPod *self, const char *type_name,
   gconstpointer value);

WP_API
gboolean wp_spa_pod_set_fd (WpSpaPod *self, gint64 value);

WP_API
gboolean wp_spa_pod_set_rectangle (WpSpaPod *self, guint32 width,
    guint32 height);

WP_API
gboolean wp_spa_pod_set_fraction (WpSpaPod *self, guint32 num, guint32 denom);

WP_API
gboolean wp_spa_pod_set_pod (WpSpaPod *self, const WpSpaPod *pod);

WP_API
gboolean wp_spa_pod_equal (const WpSpaPod *self, const WpSpaPod *pod);

WP_API
gboolean wp_spa_pod_get_object (const WpSpaPod *self, const char *type_name,
    const char **id_name, ...) G_GNUC_NULL_TERMINATED;

WP_API
gboolean wp_spa_pod_get_object_valist (const WpSpaPod *self,
    const char *type_name, const char **id_name, va_list args);

WP_API
gboolean wp_spa_pod_get_struct (const WpSpaPod *self, ...)
    G_GNUC_NULL_TERMINATED;

WP_API
gboolean wp_spa_pod_get_struct_valist (const WpSpaPod *self, va_list args);

WP_API
gboolean wp_spa_pod_get_property (const WpSpaPod *self, const char **key,
    WpSpaPod **value);

WP_API
gboolean wp_spa_pod_get_control (const WpSpaPod *self, guint32 *offset,
    const char **type_name, WpSpaPod **value);

WP_API
WpSpaPod *wp_spa_pod_get_choice_child (WpSpaPod *self);

WP_API
WpSpaPod *wp_spa_pod_get_array_child (WpSpaPod *self);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (WpSpaPod, wp_spa_pod_unref)


/**
 * WP_TYPE_SPA_POD_BUILDER:
 *
 * The #WpSpaPodBuilder #GType
 */
#define WP_TYPE_SPA_POD_BUILDER (wp_spa_pod_builder_get_type ())
WP_API
GType wp_spa_pod_builder_get_type (void);

typedef struct _WpSpaPodBuilder WpSpaPodBuilder;

WP_API
WpSpaPodBuilder *wp_spa_pod_builder_ref (WpSpaPodBuilder *self);

WP_API
void wp_spa_pod_builder_unref (WpSpaPodBuilder *self);

WP_API
WpSpaPodBuilder *wp_spa_pod_builder_new_array (void);

WP_API
WpSpaPodBuilder *wp_spa_pod_builder_new_choice (const char *type_name);

WP_API
WpSpaPodBuilder *wp_spa_pod_builder_new_object (const char *type_name,
    const char *id_name);

WP_API
WpSpaPodBuilder *wp_spa_pod_builder_new_struct (void);

WP_API
WpSpaPodBuilder *wp_spa_pod_builder_new_sequence (guint unit);

WP_API
void wp_spa_pod_builder_add_none (WpSpaPodBuilder *self);

WP_API
void wp_spa_pod_builder_add_boolean (WpSpaPodBuilder *self, gboolean value);

WP_API
void wp_spa_pod_builder_add_id (WpSpaPodBuilder *self, guint32 value);

WP_API
void wp_spa_pod_builder_add_int (WpSpaPodBuilder *self, gint value);

WP_API
void wp_spa_pod_builder_add_long (WpSpaPodBuilder *self, glong value);

WP_API
void wp_spa_pod_builder_add_float (WpSpaPodBuilder *self, float value);

WP_API
void wp_spa_pod_builder_add_double (WpSpaPodBuilder *self, double value);

WP_API
void wp_spa_pod_builder_add_string (WpSpaPodBuilder *self, const char *value);

WP_API
void wp_spa_pod_builder_add_bytes (WpSpaPodBuilder *self, gconstpointer value,
    guint32 len);

WP_API
void wp_spa_pod_builder_add_pointer (WpSpaPodBuilder *self,
    const char *type_name, gconstpointer value);

WP_API
void wp_spa_pod_builder_add_fd (WpSpaPodBuilder *self, gint64 value);

WP_API
void wp_spa_pod_builder_add_rectangle (WpSpaPodBuilder *self, guint32 width,
    guint32 height);

WP_API
void wp_spa_pod_builder_add_fraction (WpSpaPodBuilder *self, guint32 num,
    guint32 denom);

WP_API
void wp_spa_pod_builder_add_pod (WpSpaPodBuilder *self, const WpSpaPod *pod);

WP_API
void wp_spa_pod_builder_add_property (WpSpaPodBuilder *self, const char *key);

WP_API
void wp_spa_pod_builder_add_control (WpSpaPodBuilder *self, guint32 offset,
    const char *type_name);

WP_API
void wp_spa_pod_builder_add (WpSpaPodBuilder *self, ...) G_GNUC_NULL_TERMINATED;

WP_API
void wp_spa_pod_builder_add_valist (WpSpaPodBuilder *self, va_list args);

WP_API
WpSpaPod *wp_spa_pod_builder_end (WpSpaPodBuilder *self);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (WpSpaPodBuilder, wp_spa_pod_builder_unref)


/**
 * WP_TYPE_SPA_POD_PARSER:
 *
 * The #WpSpaPodParser #GType
 */
#define WP_TYPE_SPA_POD_PARSER (wp_spa_pod_parser_get_type ())
WP_API
GType wp_spa_pod_parser_get_type (void);

typedef struct _WpSpaPodParser WpSpaPodParser;

WP_API
WpSpaPodParser *wp_spa_pod_parser_ref (WpSpaPodParser *self);

WP_API
void wp_spa_pod_parser_unref (WpSpaPodParser *self);

WP_API
WpSpaPodParser *wp_spa_pod_parser_new_object (const WpSpaPod *pod,
    const char *type_name, const char **id_name);

WP_API
WpSpaPodParser *wp_spa_pod_parser_new_struct (const WpSpaPod *pod);

WP_API
gboolean wp_spa_pod_parser_get_boolean (WpSpaPodParser *self, gboolean *value);

WP_API
gboolean wp_spa_pod_parser_get_id (WpSpaPodParser *self, guint32 *value);

WP_API
gboolean wp_spa_pod_parser_get_int (WpSpaPodParser *self, gint *value);

WP_API
gboolean wp_spa_pod_parser_get_long (WpSpaPodParser *self, glong *value);

WP_API
gboolean wp_spa_pod_parser_get_float (WpSpaPodParser *self, float *value);

WP_API
gboolean wp_spa_pod_parser_get_double (WpSpaPodParser *self, double *value);

WP_API
gboolean wp_spa_pod_parser_get_string (WpSpaPodParser *self,
    const char **value);

WP_API
gboolean wp_spa_pod_parser_get_bytes (WpSpaPodParser *self,
    gconstpointer *value, guint32 *len);

WP_API
gboolean wp_spa_pod_parser_get_pointer (WpSpaPodParser *self,
    const char **type_name, gconstpointer *value);

WP_API
gboolean wp_spa_pod_parser_get_fd (WpSpaPodParser *self, gint64 *value);

WP_API
gboolean wp_spa_pod_parser_get_rectangle (WpSpaPodParser *self, guint32 *width,
    guint32 *height);

WP_API
gboolean wp_spa_pod_parser_get_fraction (WpSpaPodParser *self, guint32 *num,
    guint32 *denom);

WP_API
WpSpaPod *wp_spa_pod_parser_get_pod (WpSpaPodParser *self);

WP_API
gboolean wp_spa_pod_parser_get (WpSpaPodParser *self, ...);

WP_API
gboolean wp_spa_pod_parser_get_valist (WpSpaPodParser *self,
    va_list args);

WP_API
void wp_spa_pod_parser_end (WpSpaPodParser *self);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (WpSpaPodParser, wp_spa_pod_parser_unref)


WP_API
WpIterator *wp_spa_pod_iterator_new (const WpSpaPod *pod);

G_END_DECLS

#endif