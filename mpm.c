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

    // Lets init git and stuff
    int pid = fork();

    if(pid == 0) {

        // Change dir to project
        chdir(final_path);

        // Buffers for git info
        char git_username[128] = "";
        char git_token[128] = "";

        // Get username
        for(int i = 0; i < 1; i++) {
            fgets(git_username, sizeof(git_username), cfg);
        }

        git_username[strcspn(git_username, "\n")] = 0;

        // Get Token
        for(int i = 0; i < 2; i++) {
            fgets( git_token, sizeof(git_token), cfg);
        }

        git_token[strcspn(git_token, "\n")] = 0;

        // For creating a curl remote repo cmd
        char curl_cmd[128] = "";
        char remote_repo1[128] = "curl -u ";
        char remote_repo2[128] = " https://api.github.com/user/repos -d '{\"name\":\"";
        char remote_repo3[128] = "\"}'";
        char colon[1] = ":";
        
        strcat(curl_cmd, remote_repo1);
        strcat(curl_cmd, git_username);
        strcat(curl_cmd, colon);
        strcat(curl_cmd, git_token);
        strcat(curl_cmd, remote_repo2);
        strcat(curl_cmd, pname);
        strcat(curl_cmd, remote_repo3);

        printf("%s\n", curl_cmd);

        // cmd for adding remote origin
        char remote_add[128] = "";
        char origin1[128] = "git remote add origin git@github.com:";
        char origin2[128] = "/";
        char origin3[128] = ".git";

        strcat(remote_add, origin1);
        strcat(remote_add, git_username);
        strcat(remote_add, origin2);
        strcat(remote_add, pname);
        strcat(remote_add, origin3);

        printf("%s\n", remote_add);

        // Let's have some pleasure
        system("git init");
        system(curl_cmd);
        system(remote_add);

    } else {
        // I want to change the current working dir or open up new terminal with the final_path
        wait(NULL);
    }

    // And like ted mosby, close all your relations... in our case it's the file pointer
    fclose(cfg);

    // Wanna know my fav prime
    return 73;

}
