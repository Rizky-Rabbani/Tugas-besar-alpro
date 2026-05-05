#include "website.h"

const WebSite database[] = 
{
    {
        "resepmasak.com",
        "telor 1 butir, garam 100 gram, lada 50 gram"
    },
    
    {
        "gadgetreview.com",
        "Iphone 18 jelek, gausa beli, kualitas turun, ancur"
    },
    
    {
        "jualbeliikanhias.com",
        "-Dijual ikan cupang argentina, 800 ribu NETT\n-Dijual bibit hiu putih Brazil"
    },
    
    {
        "jualbelisepedabekas.com",
        "-WTS Trek Emonda Shimano Tiagra 19jt NETT\n-WTB road bike carbon bekas, budget max 500 ribu"
    }

};

const int jumlah_website = sizeof(database) / sizeof(database[0]);