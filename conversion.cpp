#include "conversion.h"


string CONVERSION::Unite(int n)
   {
       string val[]={" zéro "," un "," deux "," trois "," quatre "," cinq "," six "," sept "," huit "," neuf "};
       if(n>9)return Dizaine(n);
       else return val[n];
   }
 string  CONVERSION:: Dizaine(int n)
   {
       string val1[]={" dix "," onze "," douze "," treize "," quatorze "," quinze "," seize "," dix-sept "," dix-huit "," dix-neuf "};
       string val2[]={"","dix"," vingt "," trente "," quarante "," cinquante "," soixante "," soixante-dix "," quatre-vingt "," quatre-vingt-dix "};
       int p=n/10,d=n%10;
       if(p==0)return Unite(n);
       else if(p>9)return Centaine(n);
       else if(p==1) return val1[d];
       else if(d==0) return val2[p];
       else if(p==7 || p==7)return val2[p-1]+val1[d];
       else if(d==1 && p!=8)return val2[p]+"un";
      else if(p==8 && d==1) return val2[p]+"et un";
       else return val2[p]+Unite(d);
   }

  string CONVERSION:: Centaine(int n)
   {
       string c=" cent";
       int p=n/100,d=n%100;
       if(p==0)return Dizaine(n);
       else if(p>9) return Mille(n);
       else if(p==1 && d==0) return c;
       else if(p==1) return c+Dizaine(d);
       else if(d==0) return Unite(p)+c;
       else return Unite(p)+c+Dizaine(d);
   }

   string CONVERSION:: Mille(int n)
   {
    string m=" mille";
    int p=n/1000,d=n%1000;
    if(p==0) return Centaine(d);
    else if(p>=1000)return Million(n);
    else if(p==1 && d==0) return m;
    else if(p==1 && d!=0) return m+Centaine(d);
    else if(d==0) return Unite(p)+m;
    else return Centaine(p)+m+Centaine(d);
   }
   string CONVERSION:: Million(int n)
   {
      string m=" million";
    int p=n/1000000,d=n%1000000;
    if(p==0) return Mille(n);
    else if(p>=1000)return Milliard(n);
    else if(p==1 && d==0) return Unite(p)+m;
    else if(p==1)return Unite(p)+m+Mille(d);
    else if(d==0) return Centaine(p)+m+"s";
    else return Centaine(p)+m+"s"+Mille(d);
   }

   string CONVERSION:: Milliard(int n)
   {
    string m=" milliard";
    int p=n/1000000000,d=n%1000000000;
    if(p==0) return Million(n);
    else if(p>=1000)return "Be loatsy";
    else if(p==1 && d==0) return Unite(p)+m;
    else if(p==1)return Unite(p)+m+Million(d);
    else if(d==0) return Centaine(p)+m+"s";
    else return Centaine(p)+m+"s"+Million(d);
   }

   CONVERSION::CONVERSION(){}

    string CONVERSION::Convertir(double d)
    {
        return Milliard(d);
    }
    string CONVERSION:: Convertir(int d)
    {
        return Milliard((double)d);
    }
