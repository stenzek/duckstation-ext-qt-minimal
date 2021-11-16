/* Generated by wayland-scanner 1.17.0 */

#ifndef SERVER_BUFFER_EXTENSION_SERVER_PROTOCOL_H
#define SERVER_BUFFER_EXTENSION_SERVER_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-server-core.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct wl_client;
struct wl_resource;

/**
 * @page page_server_buffer_extension The server_buffer_extension protocol
 * @section page_ifaces_server_buffer_extension Interfaces
 * - @subpage page_iface_qt_server_buffer - buffers managed by the compositor
 * @section page_copyright_server_buffer_extension Copyright
 * <pre>
 *
 * Copyright (C) 2015 The Qt Company Ltd.
 * Contact: http://www.qt.io/licensing/
 *
 * This file is part of the plugins of the Qt Toolkit.
 *
 * $QT_BEGIN_LICENSE:BSD$
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the
 * distribution.
 * * Neither the name of The Qt Company Ltd nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 *
 * $QT_END_LICENSE$
 * </pre>
 */
struct qt_server_buffer;

/**
 * @page page_iface_qt_server_buffer qt_server_buffer
 * @section page_iface_qt_server_buffer_desc Description
 *
 * Server buffer is an extension which makes it possible to share a
 * buffer created by the compositor to share it with arbitrary
 * clients. These types of buffers are intended to be read only
 * buffers for clients, but this is an implementation detail.
 *
 * Server buffers main purpose is to help implement caches
 * @section page_iface_qt_server_buffer_api API
 * See @ref iface_qt_server_buffer.
 */
/**
 * @defgroup iface_qt_server_buffer The qt_server_buffer interface
 *
 * Server buffer is an extension which makes it possible to share a
 * buffer created by the compositor to share it with arbitrary
 * clients. These types of buffers are intended to be read only
 * buffers for clients, but this is an implementation detail.
 *
 * Server buffers main purpose is to help implement caches
 */
extern const struct wl_interface qt_server_buffer_interface;

/**
 * @ingroup iface_qt_server_buffer
 * @struct qt_server_buffer_interface
 */
struct qt_server_buffer_interface {
	/**
	 */
	void (*release)(struct wl_client *client,
			struct wl_resource *resource);
};


/**
 * @ingroup iface_qt_server_buffer
 */
#define QT_SERVER_BUFFER_RELEASE_SINCE_VERSION 1

#ifdef  __cplusplus
}
#endif

#endif
