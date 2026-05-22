#include "website.h"
#include <stdio.h>

void printGajah() {
    // \033[0;34m untuk warna biru
    // \033[0m untuk mereset warna kembali ke normal
    printf("\033[0;34m"); 
    printf("       _  _          \n");
    printf("     _( \033[0;31m\"\" \033[0;34m)_        \n"); // Bagian mata diberi warna merah
    printf("   _(_  ..  |_)      \n");
    printf("  (_ ` _ \033[0;33m--\033[0;34m _ ` )     \n"); // Gading warna kuning
    printf("    (_(_)(_)(_)      \n");
    printf("\033[0m"); 
}

void printHarimau() {
    printf("\033[0;33m"); // Warna Oranye/Kuning
    printf("   \\|\\      /|/   \n");
    printf("    \\ \\____/ /    \n");
    printf("    /_  __  _\\    \n");
    printf("   (  (  )   )    \n");
    printf("    \\  --  /     \n");
    printf("     ||  ||       \n");
    printf("\033[0m");
}

void printGajahArt() {
    // Gunakan warna abu-abu/putih (standar) atau biru untuk gajah
    printf("\033[0;34m"); 
    printf("\t                     ___     _,.--.,_ \n");
    printf("\t                  .-~   ~--\"~-.   ._ \"-. \n");
    printf("\t                 /      ./_    Y    \"-. \\ \n");
    printf("\t                Y       :~     !         Y \n");
    printf("\t                lq p    |     /         .| \n");
    printf("\t             _   \\. .-, l    /          |j \n");
    printf("\t            ()\\___) |/   \\_/\";          ! \n");
    printf("\t             \\._____.-~\\  .  ~\\.      ./ \n");
    printf("\t                        Y_ Y_. \"vr\"~  T \n");
    printf("\t                        (  (    |L    j   -Row \n");
    printf("\t                        [nn[nn..][nn..] \n");
    printf("\t                    ~~~~~~~~~~~~~~~~~~~~~~~ \n");
    printf("\033[0m"); // Reset warna
}

void printAnya() {
    printf("\033[1;35m"); // Warna pink/magenta terang
    printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢲⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠄⠂⢉⠤⠐⠋⠈⠡⡈⠉⠐⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⢀⡀⢠⣤⠔⠁⢀⠀⠀⠀⠀⠀⠀⠀⠈⢢⠀⠀⠈⠱⡤⣤⠄⣀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠰⠁⠀⣰⣿⠃⠀⢠⠃⢸⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠈⢞⣦⡀⠈⡇⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⢇⣠⡿⠁⠀⢀⡃⠀⣈⠀⠀⠀⠀⢰⡀⠀⠀⠀⠀⢢⠰⠀⠀⢺⣧⢰⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠈⣿⠁⡘⠀⡌⡇⠀⡿⠸⠀⠀⠀⠈⡕⡄⠀⠐⡀⠈⠀⢃⠀⠀⠾⠇⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠇⡇⠃⢠⠀⠶⡀⡇⢃⠡⡀⠀⠀⠡⠈⢂⡀⢁⠀⡁⠸⠀⡆⠘⡀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠸⠀⢸⠀⠘⡜⠀⣑⢴⣀⠑⠯⡂⠄⣀⣣⢀⣈⢺⡜⢣⠀⡆⡇⠀⢣⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠇⠀⢸⠀⡗⣰⡿⡻⠿⡳⡅⠀⠀⠀⠀⠈⡵⠿⠿⡻⣷⡡⡇⡇⠀⢸⣇⠀⠀⠀\n");
    printf("\t\t⠀⠀⢰⠀⠀⡆⡄⣧⡏⠸⢠⢲⢸⠁⠀⠀⠀⠀⠐⢙⢰⠂⢡⠘⣇⡇⠃⠀⠀⢹⡄⠀⠀\n");
    printf("\t\t⠀⠀⠟⠀⠀⢰⢁⡇⠇⠰⣀⢁⡜⠀⠀⠀⠀⠀⠀⠘⣀⣁⠌⠀⠃⠰⠀⠀⠀⠈⠰⠀⠀\n");
    printf("\t\t⠀⡘⠀⠀⠀⠀⢊⣤⠀⠀⠤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⠄⠀⢸⠃⠀⠀⠀⠀⠀⠃⠀\n");
    printf("\t\t⢠⠁⢀⠀⠀⠀⠈⢿⡀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⢀⠏⠀⠀⠀⠀⠀⠀⠸⠀\n");
    printf("\t\t⠘⠸⠘⡀⠀⠀⠀⠀⢣⠀⠀⠀⠀⠀⠀⠁⠀⠃⠀⠀⠀⠀⢀⠎⠀⠀⠀⠀⠀⢠⠀⠀⡇\n");
    printf("\t\t⠀⠇⢆⢃⠀⠀⠀⠀⠀⡏⢲⢤⢀⡀⠀⠀⠀⠀⠀⢀⣠⠄⡚⠀⠀⠀⠀⠀⠀⣾⠀⠀⠀\n");
    printf("\t\t⢰⠈⢌⢎⢆⠀⠀⠀⠀⠁⣌⠆⡰⡁⠉⠉⠀⠉⠁⡱⡘⡼⠇⠀⠀⠀⠀⢀⢬⠃⢠⠀⡆\n");
    printf("\t\t⠀⢢⠀⠑⢵⣧⡀⠀⠀⡿⠳⠂⠉⠀⠀⠀⠀⠀⠀⠀⠁⢺⡀⠀⠀⢀⢠⣮⠃⢀⠆⡰⠀\n");
    printf("\t\t⠀⠀⠑⠄⣀⠙⡭⠢⢀⡀⠀⠁⠄⣀⣀⠀⢀⣀⣀⣀⡠⠂⢃⡀⠔⠱⡞⢁⠄⣁⠔⠁⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠉⠁⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀\n");
    printf("\033[0m"); // Reset warna ke normal
}

void printCenturion() {
    printf("\033[1;31m"); // Mengubah warna teks menjadi merah
    printf("______________________   _____________  ____________________________   __\n");
    printf("__  ____/__  ____/__  | / /__  __/_  / / /__  __ \\___  _/_  __ \\__  | / /\n");
    printf("_  /    __  __/  __   |/ /__  /  _  / / /__  /_/ /__  / _  / / /_   |/ / \n");
    printf("/ /___  _  /___  _  /|  / _  /   / /_/ / _  _, _/__/ /  / /_/ /_  /|  /  \n");
    printf("\\____/  /_____/  /_/ |_/  /_/    \\____/  /_/ |_| /___/  \\____/ /_/ |_/   \n");
    printf("\033[0m");    // Reset warna terminal ke default
}

void printExit() {
    printf("\033[1;31m"); // Mengubah warna teks menjadi merah bold
    printf("    ___          _____  ____________           ___\n");
    printf("   / _/         / __/ |/_/  _/_  __/          /  /\n");
    printf("  / /          / _/_>  <_/ /  / /             / / \n");
    printf(" / /          /___/_/|_/___/ /_/            _/ /  \n");
    printf("/__/                                       /__/   \n");
    printf("\033[0m");    // Reset warna terminal ke default
}

void printAnonym() {
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("                                             ######%%%%%%%%%%####                                       \n");
    printf("                                          ##%%%%%%_@@@@@@@%%%%%%%%                                     \n");
    printf("                                         #@@%%@@@%%##**##%%%%%%@@%%%%                                    \n");
    printf("                                        #%%_%%%%*+======++**%%@%%@%%                                   \n");
    printf("                                        %%%%%%#+==-------==*#@@%%                                   \n");
    printf("                                        %%%%%%#+==-------==++#@@@%%                                  \n");
    printf("                                        %%@@@%%*+==--------==+#%%@@%%                                  \n");
    printf("                                        ##%%#***+++++===++++++*#%%                                   \n");
    printf("                                        *#*==+++=++==-===++++++*%%                                  \n");
    printf("                                       +*%%+===++*+========+++==+%%#                                  \n");
    printf("                                       ++*+==------======-----=+** \n");
    printf("                                        =++===-----======----==+++                                  \n");
    printf("                                        ==++===----=++++=---===+==                                  \n");
    printf("                                         ==++====--======--===++=                                   \n");
    printf("                                           +++=========+======++                                    \n");
    printf("                                           ++++++++======+++++* \n");
    printf("                                            ***+++++++++++++** \n");
    printf("                                          ####**+++++===+++**##                                     \n");
    printf("                                    ++***#%%#*#**#*++++++++***###** \n");
    printf("                                 ==++*********#**##%%%%##*++####%%#** \n");
    printf("                        # * ++++++**#********#*++******+++*#####@#******* \n");
    printf("                      +******+++****##********%%%%++++***++++#*####%%%%#******#***** \n");
}

void printGoodBye() {
    printf("\033[1;36m"); // Mengubah warna teks menjadi Cyan Bold
    printf("            _____             _____                    \n");
    printf(" ________  / ___/__  ___  ___/ / _ )__ _____   ________\n");
    printf("/___/___/ / (_ / _ \\/ _ \\/ _  / _  / // / -_) /___/___/\n");
    printf("          \\___/\\___/\\___/\\_,_/____/\\_, /\\__/           \n");
    printf("                                  /___/                \n");
    printf("\033[0m");    // Reset warna terminal ke default
}