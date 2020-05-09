#include<stdio.h>
#include <string.h>

int status;
FILE *fp_1;
/* the term form */
char department[50][50], date[50][50], name[50][50], site[50][50], phone[50][50], item[50][50], condition[50][50]
     ,account[50];
 int i=0;

void sign_in_system(void);
void form_open(void);
void administrator(void);
void guest(void);
void add_matter(void);
void respond(void);
void modify(void);
void Delete(void);

int main(void)
{
    sign_in_system();
    form_open();
    switch(status){
        case 1: administrator(); break;
        case 2: guest(); break;
    }
}

void sign_in_system(void)
{
    int test_account, test_password;
    char password[20], *account_adm="imadministrator", *password_adm="123456789";
    printf("Please choose your status to sign in.\n");
    printf("Press 1 if you are administrator\n");
    printf("Press 2 if you are guest\n");
    while(1){
        scanf("%d", &status);
        if(status==1||status==2){
            break;
        }
        else
            printf("Error,Please enter 1 or 2.\n");
        }
    /* administrator sign in */
    while(status==1){
        printf("Please enter your account number and password\n");
        printf("Account number:");
        scanf("%s", account);
        printf("Password:");
        scanf("%s", password);
        test_account = strcmp(account, account_adm);/* verify account */
        test_password = strcmp(password, password_adm);/* verify password */
        if(test_account==0&&test_password==0){
            printf("sign in successfully\n");
            break;
            }
        else if(test_account!=0)
            printf("Wrong account number\n");
        else if(test_account==0&&test_password!=0)
            printf("Wrong password\n");
    }
    /* guest sign in */
    while(status==2){
        printf("Please enter your name\n");
        printf("name:");
        scanf("%s", account);
        printf("sign in successfully\n");
        break;
    }
}

void form_open(void)/* print the form */
{
    char ch;
    fp_1 = fopen("repair.txt", "r");
    fscanf(fp_1, "%s%s%s%s%s%s%s",department[i], date[i], name[i], site[i], phone[i], item[i], condition[i]);
    printf("%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
          department[i], date[i], name[i], site[i], phone[i], item[i], condition[i]);
    i++;
    while((ch = fgetc(fp_1)) != EOF){
        fscanf(fp_1, "%s%s%s%s%s%s%s",department[i], date[i], name[i], site[i], phone[i], item[i], condition[i]);
        printf("%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
              department[i], date[i], name[i], site[i], phone[i], item[i], condition[i]);
        i++;
    }
    i--;
    fclose(fp_1);
}

void administrator(void)
{
    int act;
    while(1){
        printf("--------------------------------\n");
        printf("|If you want to respond press 1|\n");
        printf("|If you want to delete press 2 |\n");
        printf("|If you want to leave press 3  |\n");
        printf("--------------------------------\n");
        printf("your act:");
        scanf("%d", &act);
        if(act==1)
            respond();
        else if(act==2)
            Delete();
        else if(act==3){
            printf("Sign out successfully\n");
            break;
        }
    }
}

void guest(void)
{
    int act;
    while(1){
        printf("-----------------------------------------------\n");
        printf("|If you want to add new matter, please press 1|\n");
        printf("|If you want to modify,please press 2         |\n");
        printf("|If you want to delete, please press 3        |\n");
        printf("|If you want to leave press 4                 |\n");
        printf("-----------------------------------------------\n");
        printf("your act:");
        scanf("%d", &act);
        if(act==4){
            printf("Sign out successfully\n");
            break;
        }
        switch(act){
            case 1:add_matter();break;
            case 2:modify();break;
            case 3:Delete();break;
        }
    }
}

void add_matter()/* guest---add mater */
{
     int save, j=0;
     while(1){
         printf("單位:");
         scanf("%s", department[i]);
         printf("報修日期:");
         scanf("%s", date[i]);
         printf("地點:");
         scanf("%s", site[i]);
         printf("電話:");
         scanf("%s", phone[i]);
         printf("故障項目:");
         scanf("%s", item[i]);
         strcpy(condition[i], "未處理");
         strcpy(name[i], account);
         i++;
         fp_1 = fopen("repair.txt", "w");
         system("cls");
         for(j=0; j<i; j++){ /*the form that have been changed */
             printf("%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                   department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);

             fprintf(fp_1, "%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);
         }
         fclose(fp_1);
         printf("Do you want to add other matters? press 1 to continue, press 2 to leave:");
         scanf("%d", &save);
         if(save==2)
             break;
     }
}

void respond()/* administrator---respond */
{
    int row, j=0, solve, save;
    while(1){
        printf("Enter the row that you want to respond:");
        scanf("%d", &row);
        if(row<i){
            if(strcmp(condition[row], "未處理")==0)
                strcpy(condition[row], "處理中");
            else if(strcmp(condition[row], "處理中")==0){
                printf("Weather the problem been solved?\n");
                printf("If solved press 1, if not press 2:");/* solve---successful or fail */
                while(1){
                    scanf("%d", &solve);
                    if(solve==1){
                        strcpy(condition[row], "處理完畢");
                        break;
                    }
                    else if(solve==2){
                        strcpy(condition[row], "處理失敗");
                        break;
                    }
                    else
                        printf("Plese press 1 or 2\n");
                }
            }
            else
                break;
            system("cls");
            fp_1 = fopen("repair.txt", "w");
            for(j=0;j<i;j++){ /*the form that have been changed */
                printf("%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                      department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);
                fprintf(fp_1, "%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                       department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);
            }

            fclose(fp_1);
            printf("Do you want to respond other matters? press 1 to continue, press 2 to leave:");
            scanf("%d", &save);
            if(save==2)
                break;
        }

        else{
            printf("-----------------------------------------\n");
            printf("|Not existed, Please enter the number<=%d|\n", i-1);
            printf("-----------------------------------------\n");
        }
    }
}

void modify(void)/* guest---modify */
{
    int row, j=0, save;
    while(1){
        printf("Enter the row that you want to modify:");
        scanf("%d", &row);
        if(row<i&&strcmp(name[row], account)==0){/* the differentiate of row and person */
            printf("單位:");
            scanf("%s", department[row]);
            printf("報修日期:");
            scanf("%s", date[row]);
            printf("地點:");
            scanf("%s", site[row]);
            printf("故障項目:");
            scanf("%s", item[row]);
            strcpy(condition[row], "未處理");
            strcpy(name[i], account);
            fp_1 = fopen("repair.txt", "w");
            system("cls");
            for(j=0; j<i; j++){ /*the form that have been changed */
                 printf("%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                       department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);

                 fprintf(fp_1, "%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                        department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);
            }
            fclose(fp_1);
            printf("Do you want to modify other matters? press 1 to continue, press 2 to leave:");
            scanf("%d", &save);
            if(save==2)
                break;
        }
        else if(row>=i){
            printf("-----------------------------------------\n");
            printf("|Not existed, Please enter the number<=%d|\n", i-1);
            printf("-----------------------------------------\n");
        }
        else if(strcmp(name[row], account)==1){
            printf("------------------------------------\n");
            printf("|You are not the original applicant|\n");
            printf("------------------------------------\n");
            break;
        }
    }
}

void Delete(void)
{
    int row, j=0, save;
    while(1){
        printf("Enter the row that you want to delete:");
        scanf("%d", &row);
        if(row<i&&strcmp(name[row], account)==0){/* the differentiate of row and person */
            for(;(row+1)<=i;row++){/* use loop to delete with the motion of replacement */
                strcpy(department[row], department[row+1]);
                strcpy(date[row], date[row+1]);
                strcpy(name[row], name[row+1]);
                strcpy(site[row], site[row+1]);
                strcpy(phone[row], phone[row+1]);
                strcpy(item[row], item[row+1]);
                strcpy(condition[row], condition[row+1]);
            }
            i--;
            fp_1 = fopen("repair.txt", "w");
            system("cls");
            for(j=0; j<i; j++){ /*the form that have been changed */
                printf("%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                      department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);

                fprintf(fp_1, "%-5s\t%-8s\t%-5s\t%-7s\t%-10s\t%-8s\t%-4s\n",
                       department[j], date[j], name[j], site[j], phone[j], item[j], condition[j]);
            }
            fclose(fp_1);
            printf("Do you want to delete other matters? press 1 to continue, press 2 to leave:");
            scanf("%d", &save);
            if(save==2)
                break;
        }
        else if(row>=i){
            printf("-----------------------------------------\n");
            printf("|Not existed, Please enter the number<=%d|\n", i-1);
            printf("-----------------------------------------\n");
        }
        else if(strcmp(name[row], account)==1){
            printf("------------------------------------\n");
            printf("|You are not the original applicant|\n");
            printf("------------------------------------\n");
            break;
        }
    }
}
