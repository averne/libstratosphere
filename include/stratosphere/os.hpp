/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stratosphere/os/os_common_types.hpp>
#include <stratosphere/os/os_memory_common.hpp>
#include <stratosphere/os/os_memory_permission.hpp>
#include <stratosphere/os/os_memory_heap_api.hpp>
#include <stratosphere/os/os_memory_virtual_address_api.hpp>
#include <stratosphere/os/os_managed_handle.hpp>
#include <stratosphere/os/os_process_handle.hpp>
#include <stratosphere/os/os_mutex.hpp>
#include <stratosphere/os/os_condvar.hpp>
#include <stratosphere/os/os_rw_lock.hpp>
#include <stratosphere/os/os_semaphore.hpp>
#include <stratosphere/os/os_timeout_helper.hpp>
#include <stratosphere/os/os_event.hpp>
#include <stratosphere/os/os_system_event.hpp>
#include <stratosphere/os/os_interrupt_event.hpp>
#include <stratosphere/os/os_thread_local_storage_api.hpp>
#include <stratosphere/os/os_thread.hpp>
#include <stratosphere/os/os_message_queue.hpp>
#include <stratosphere/os/os_waitable_holder.hpp>
#include <stratosphere/os/os_waitable_manager.hpp>
