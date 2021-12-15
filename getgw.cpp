#include "project.h"


using namespace std;

int GetDefaultGw ( std::string & gw )
{
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
}



/*int main()
{
  string gw;
  GetDefaultGw (gw);
  
  cout << gw << endl;


  
}*/
