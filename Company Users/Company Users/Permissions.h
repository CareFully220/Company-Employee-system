// This file includes all permission flags.

#pragma once

#define PERM_USER ( 1 << 0 )
#define PERM_ALLOWLOGIN ( 1 << 1 )
#define PERM_VIEWUSERS ( 1 << 2 )
#define PERM_VIEWINVENTORY ( 1 << 3 )
#define PERM_VIEWWORKHOURS ( 1 << 4 )
#define PERM_VIEWSALARY ( 1 << 5 )
#define PERM_MODIFYUSERS ( 1 << 6 )
#define PERM_MODIFYINVENTORY ( 1 << 7 )
#define PERM_MODIFYWORKHOURS ( 1 << 8 )
#define PERM_MODIFYSALARY ( 1 << 9 )
#define PERM_ADMIN ( 1 << 19 )

#define PERM_ROOT ( 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | 1 << 9 | 1 << 19 )