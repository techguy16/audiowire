/* WirePlumber
 *
 * Copyright © 2019 Collabora Ltd.
 *    @author George Kiagiadakis <george.kiagiadakis@collabora.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __WIREPLUMBER_CLIENT_H__
#define __WIREPLUMBER_CLIENT_H__

#include "proxy.h"

G_BEGIN_DECLS

struct pw_permission;

#define WP_TYPE_CLIENT (wp_client_get_type ())
WP_API
G_DECLARE_FINAL_TYPE (WpClient, wp_client, WP, CLIENT, WpProxy)

WP_API
void wp_client_update_permissions (WpClient * self, guint n_perm, ...);

WP_API
void wp_client_update_permissions_array (WpClient * self,
    guint n_perm, const struct pw_permission *permissions);

G_END_DECLS

#endif