////////////////////////////////////////////////////////////////////////////////
//                                                                             /
// 2012-2020 (c) Baical                                                        /
//                                                                             /
// This library is free software; you can redistribute it and/or               /
// modify it under the terms of the GNU Lesser General Public                  /
// License as published by the Free Software Foundation; either                /
// version 3.0 of the License, or (at your option) any later version.          /
//                                                                             /
// This library is distributed in the hope that it will be useful,             /
// but WITHOUT ANY WARRANTY; without even the implied warranty of              /
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU           /
// Lesser General Public License for more details.                             /
//                                                                             /
// You should have received a copy of the GNU Lesser General Public            /
// License along with this library.                                            /
//                                                                             /
////////////////////////////////////////////////////////////////////////////////
#ifndef LOCK_H
#define LOCK_H

///////////////////////////////////////////////////////////////////////////////
#include "PLock.h"

class CLock
{
    tLOCK  m_hCS;
    CLock *m_pLock;
public:
    CLock()
        : m_pLock(NULL)
    {
        LOCK_CREATE(m_hCS);
    }

    CLock(CLock *i_pLock)
        : m_pLock(i_pLock)
    {
        m_pLock->Lock();
    }

    virtual ~CLock()
    {
        if (NULL == m_pLock)
        {
            LOCK_DESTROY(m_hCS);
        }
        else
        {
            m_pLock->Unlock();
            m_pLock = NULL;
        }
    }

    inline void Lock()
    {
        LOCK_ENTER(m_hCS);
    }

    inline tBOOL Try()
    {
        return LOCK_TRY(m_hCS);
    }

    inline void Unlock()
    {
        LOCK_EXIT(m_hCS);
    }
};

#endif //LOCK_H
