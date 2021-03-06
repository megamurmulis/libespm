/*
 * records.h
 * This file is part of libespm
 *
 * Copyright (C) 2013 WrinklyNinja
 *
 * libespm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libespm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libespm. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ESPM_TES4_TES4_RECORD__
#define __ESPM_TES4_TES4_RECORD__

#include "../generic/record.h"

namespace espm {
    namespace tes4 {
        namespace TES4 {
            struct MAST {
                const Field &_field;

                MAST(const Field& field) : _field(field) {}

                std::string getString() const {
                    return std::string(_field.data, _field.dataSize - 1);  //Data should be null terminated.
                }
            };

            struct SNAM {
                const Field &_field;

                SNAM(const Field& field) : _field(field) {}

                std::string getString() const {
                    return std::string(_field.data, _field.dataSize - 1);  //Data should be null terminated.
                }
            }; 
            
            struct HEDR {
                const Field& _field;

                HEDR(const Field& field) : _field(field) {}

                float getVersion() const {
                    return *(float*)(_field.data);
                }

                uint32_t getNumRecords() const {
                    return *(uint32_t*)(_field.data + 4);
                }

                uint32_t getNextObjectID() const {
                    return *(uint32_t*)(_field.data + 8);
                }
            };

            struct Record : public espm::Record {
                Record(const espm::Record& record) : espm::Record(record) {}

                std::vector<std::string> getMasters() const {
                    std::vector<std::string> masters;
                    for(size_t i=0,max=fields.size(); i < max; ++i){
                        if (strncmp(fields[i].type,"SNAM", 4) == 0)
                            masters.push_back(MAST(fields[i]).getString());
                    }
                    return masters;
                }

                std::string getDescription() const {
                    for(size_t i=0,max=fields.size(); i < max; ++i){
                        if (strncmp(fields[i].type,"SNAM", 4) == 0)
                            return SNAM(fields[i]).getString();
                    }
                    return "";
                }

                uint32_t getNumRecords() const {
                    for(size_t i=0,max=fields.size(); i < max; ++i){
                        if (strncmp(fields[i].type,"HEDR", 4) == 0)
                            return HEDR(fields[i]).getNumRecords();
                    }
                    return 0;
                }
            };
        }
    }
}

#endif
