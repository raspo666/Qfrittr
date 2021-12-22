/*************************************************************************
 * Copyright 2021 Ralph Spitzner (rasp@spitzner.org)
 *
 * This file is part of Qfrittr - Qt FRitzbox traffic monitot.
 *
 * Qfrittr is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Qfrittr  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Qfrittr.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

#include "project.h"







using namespace std;

int GetDefaultGw ( std::string & gw )
{
#ifdef __linux__
  FILE *f;
    char line[100] , *p , *c, *g, *saveptr;
    int nRet=1;

    f = fopen("/proc/net/route" , "r");
    if (f ==NULL)
      {
        return 1;
      }
    while(fgets(line , 100 , f))
    {
        p = strtok_r(line , " \t", &saveptr);
        c = strtok_r(NULL , " \t", &saveptr);
        g = strtok_r(NULL , " \t", &saveptr);

        if(p!=NULL && c!=NULL)
        {
            if(strcmp(c , "00000000") == 0)
            {
                //printf("Default interface is : %s \n" , p);
                if (g)
                {
                    char *pEnd;
                    int ng=strtol(g,&pEnd,16);
                    //ng=ntohl(ng);
                    struct in_addr addr;
                    addr.s_addr=ng;
                    gw=std::string( inet_ntoa(addr) );
                    nRet=0;
                }
                break;
            }
        }
    }

    fclose(f);
    return nRet;

#elif _WIN32
////////////////////////////////////////////////////////
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

    /* variables used for GetIfForwardTable */
    PMIB_IPFORWARDTABLE pIpForwardTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    char szDestIp[128];
    char szMaskIp[128];
    char szGatewayIp[128];

    struct in_addr IpAddr;

    int i;

    pIpForwardTable =
        (MIB_IPFORWARDTABLE *) malloc(sizeof (MIB_IPFORWARDTABLE));
    if (pIpForwardTable == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    if (GetIpForwardTable(pIpForwardTable, &dwSize, 0) ==
        ERROR_INSUFFICIENT_BUFFER) {
        free(pIpForwardTable);
        pIpForwardTable = (MIB_IPFORWARDTABLE *) malloc(dwSize);
        if (pIpForwardTable == NULL) {
            printf("Error allocating memory\n");
            return 1;
        }
    }

    /* Note that the IPv4 addresses returned in
     * GetIpForwardTable entries are in network byte order
     */
    if ((dwRetVal = GetIpForwardTable(pIpForwardTable, &dwSize, 0)) == NO_ERROR) {
        printf("\tNumber of entries: %d\n",
               (int) pIpForwardTable->dwNumEntries);
         // {
                i=0;
            /* Convert IPv4 addresses to strings */
            IpAddr.S_un.S_addr =
                (u_long) pIpForwardTable->table[i].dwForwardNextHop;
            strcpy_s(szGatewayIp, sizeof (szGatewayIp), inet_ntoa(IpAddr));

            printf("\tRoute[%d] Next Hop: %s\n", i, szGatewayIp);
            gw =std::string( szGatewayIp);
            free(pIpForwardTable);
        return 0;
    } else {
        printf("\tGetIpForwardTable failed.\n");
        free(pIpForwardTable);
        return 1;
    }



////////////////////////////////////////////////////////
#else

#endif
}






