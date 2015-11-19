#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

MYSQL *con;

char* concat(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void check_errors(int status) {
    if(status) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
}

int main() {
    con = mysql_init(NULL);

    if(con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    char ip[100] = "", user[100] = "", password[100] = "";
    printf("Enter IP (localhost): ");
    scanf("%s", &ip);
    printf("Enter User (root): ");
    scanf("%s", &user);
    printf("Enter Password: ");
    scanf("%s", &password);

    if(strcmp(ip, " "))
        strcpy(ip, "localhost");

    if(strcmp(user, " "))
        strcpy(user, "root");

    if(mysql_real_connect(con, ip, user, password, NULL, 0, NULL, 0) == NULL) {
        check_errors(1);
    }

    check_errors(mysql_query(con, "SHOW DATABASES"));

    MYSQL_RES *result = mysql_store_result(con);
    MYSQL_ROW row;
    int i;

    printf("\n*** Databases!\n");

    while((row = mysql_fetch_row(result))) {
        for(i = 0; i < mysql_num_fields(result); i++) {
            printf("* %s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    return 0;
}