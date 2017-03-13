/*
     Copyright (C) 2016-2017 Nicolas Hiot - nicolashiot@hotmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/**
 * \file        DataStorage.hpp
 * \author      Nicolas Hiot - nicolashiot@hotmail.com
 */

#ifndef PANCAKE_DATASTORAGE_HPP
#define PANCAKE_DATASTORAGE_HPP

#include <GameLogic/Components/Component.hpp>
#include <cassert>
#include <map>

#define SET_DATA(T)                                                            \
    void set(std::string name, T data) {                                       \
        datas[name] = new T();                                                 \
        *((T *)datas[name]) = data;                                            \
    }

namespace PancakeEngine {
    /**
     * @class DataStorage
     * @brief Component made for store some datas in gameObject.
     * @sa Component
     */
    class DataStorage : public Component {
    public:
        SET_DATA(int)

        SET_DATA(float)

        SET_DATA(unsigned)

        SET_DATA(long)

        SET_DATA(double)

        SET_DATA(bool)

        SET_DATA(char)

        SET_DATA(char*)

        SET_DATA(std::string)

        SET_DATA(void *)

        /**
         * @brief Get a data by name.
         * @tparam T the type you want to get.
         * @param name the name of the data.
         * @return the data with the name of type T.
         */
        template<typename T>
        T get(std::string name) {
            return *((T *) datas[name]);
        }

    private:
        std::map<std::string, void *> datas;
    };
}

#endif // PANCAKE_DATASTORAGE_HPP
