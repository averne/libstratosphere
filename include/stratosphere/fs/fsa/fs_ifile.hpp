/*
 * Copyright (c) 2018-2019 Atmosphère-NX
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
#include "../fs_common.hpp"
#include "../fs_file.hpp"
#include "../fs_operate_range.hpp"

namespace ams::fs::fsa {

    class IFile {
        public:
            virtual ~IFile() { /* ... */ }

            Result Read(size_t *out, s64 offset, void *buffer, size_t size, const ReadOption &option) {
                R_UNLESS(out != nullptr, fs::ResultNullptrArgument());
                if (size == 0) {
                    *out = 0;
                    return ResultSuccess();
                }
                R_UNLESS(buffer != nullptr, fs::ResultNullptrArgument());
                R_UNLESS(offset >= 0, fs::ResultOutOfRange());
                const s64 signed_size = static_cast<s64>(size);
                R_UNLESS(signed_size >= 0, fs::ResultOutOfRange());
                R_UNLESS((std::numeric_limits<s64>::max() - offset) >= signed_size, fs::ResultOutOfRange());
                return this->ReadImpl(out, offset, buffer, size, option);
            }

            Result Read(size_t *out, s64 offset, void *buffer, size_t size) {
                return this->Read(out, offset, buffer, size, ReadOption::None);
            }

            Result GetSize(s64 *out) {
                R_UNLESS(out != nullptr, fs::ResultNullptrArgument());
                return this->GetSizeImpl(out);
            }

            Result Flush() {
                return this->FlushImpl();
            }

            Result Write(s64 offset, const void *buffer, size_t size, const WriteOption &option) {
                if (size == 0) {
                    if (option.HasFlushFlag()) {
                        R_TRY(this->Flush());
                    }
                    return ResultSuccess();
                }
                R_UNLESS(buffer != nullptr, fs::ResultNullptrArgument());
                R_UNLESS(offset >= 0, fs::ResultOutOfRange());
                const s64 signed_size = static_cast<s64>(size);
                R_UNLESS(signed_size >= 0, fs::ResultOutOfRange());
                R_UNLESS((std::numeric_limits<s64>::max() - offset) >= signed_size, fs::ResultOutOfRange());
                return this->WriteImpl(offset, buffer, size, option);
            }

            Result SetSize(s64 size) {
                R_UNLESS(size >= 0, fs::ResultOutOfRange());
                return this->SetSizeImpl(size);
            }

            Result OperateRange(void *dst, size_t dst_size, OperationId op_id, s64 offset, s64 size, const void *src, size_t src_size) {
                return this->OperateRangeImpl(dst, dst_size, op_id, offset, size, src, src_size);
            }

            Result OperateRange(OperationId op_id, s64 offset, s64 size) {
                return this->OperateRangeImpl(nullptr, 0, op_id, offset, size, nullptr, 0);
            }
        public:
            /* TODO: This is a hack to allow the mitm API to work. Find a better way? */
            virtual sf::cmif::DomainObjectId GetDomainObjectId() const = 0;
        protected:
            /* ...? */
        private:
            virtual Result ReadImpl(size_t *out, s64 offset, void *buffer, size_t size, const ReadOption &option) = 0;
            virtual Result GetSizeImpl(s64 *out) = 0;
            virtual Result FlushImpl() = 0;
            virtual Result WriteImpl(s64 offset, const void *buffer, size_t size, const WriteOption &option) = 0;
            virtual Result SetSizeImpl(s64 size) = 0;
            virtual Result OperateRangeImpl(void *dst, size_t dst_size, OperationId op_id, s64 offset, s64 size, const void *src, size_t src_size) = 0;
    };

}
