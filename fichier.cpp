#include "fichier.h"
#include "affaire.h"


void CreeFichier(char *fnam)
{
    FILE*fd=fopen(fnam,"r");
    if(fd!=NULL)
    {
        fclose(fd);
    }
    else
    {
        fd=fopen(fnam,"w");
        fclose(fd);
    }
}
void initialiser()
{
    CreeFichier(FCLI);
    CreeFichier(FMAT);
    CreeFichier(FCOM);
    CreeFichier(FCOM1);
    CreeFichier(FAFF);
    CreeFichier(FTMP1);
    CreeFichier(FFACT);

}
