#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
     
    // Lets get and set our project name as pname
    char *pname = argv[1];
    char root_path[128] = "";
    char final_path[128] = "";
     
    // Lets get our config file as cfg
    FILE *cfg;
    char cfg_buff[128];
    cfg = fopen("./mpm.conf", "r");

    // Lets read our project dir path
    for(int i = 0; i < 1; i++) {
        fgets(cfg_buff, sizeof(cfg_buff), cfg);
    }

    // Remove the EOL (end of line from our path)
    cfg_buff[strcspn(cfg_buff, "\n")] = 0;
    
    // Concat the path with our project name
    strcat(final_path, cfg_buff);
    strcat(final_path, pname);

    // Make a folder at the destination
    mkdir(final_path, 0777);

    // And like ted mosby close all your relations... in this case the file pointer
    fclose(cfg);

    // Lets inti git and stuff

    char gitcmd[128] = "git init ";
    char cd[128] = "cd ";

    strcat(gitcmd, final_path);
    int status = system(gitcmd);

    strcat(cd, final_path);
    int s2 = system(cd);
    

    return 73;

}
