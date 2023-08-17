#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define cls system("cls");
#define etr printf("Press ENTER to continue...\n");

// PAYMENT METHOD
char method[3][10] = {"Cash", "Cashless"};

// STRUCT SERBA GUNA
struct dot{
    char name[256];
    int pass;
    int total;
    int payment;
    struct pesanan *order;
    struct dot *next;
};

// BUAT LINKED LIST
struct all{
    struct dot *head, *tail;
};

// BIKIN LINKED LIST BARU
struct all *newList(){
    struct all *s = (struct all *)malloc(sizeof(struct all));
    s->head =  s->tail = NULL;
}

// DELETE A LINKED LIST NODE BY NAME
int deleteNodeName(struct all *s, char name[]){
    struct dot* curr = s->head;
    if(s->head != NULL){
        if(strcmp(s->head->name,name)==0){
            s->head = curr -> next;
            free(curr);
            return 1;
        }else{
            while(curr->next != NULL && strcmp(curr->next->name, name) != 0){
                curr = curr->next;
            }
            if(curr->next != NULL){
                struct dot *temp = curr->next;
                curr->next = temp->next;
                free(temp);
                return 1;
            }
        }
    }
    return 0;
}

// DELETE A LINKED LIST NODE BY TNUM
int deleteNodeTable(struct all *s, int x){
    struct dot* curr = s->head;
    if(s->head != NULL){
        if(s->head->pass == x){
            s->head = curr -> next;
            free(curr);
            return 1;
        }else{
            while(curr->next != NULL && s->head->pass != x){
                curr = curr->next;
            }
            if(curr->next != NULL){
                struct dot *temp = curr->next;
                curr->next = temp->next;
                free(temp);
                return 1;
            }
        }
    }
    return 0;
}

// CARI LINKED LIST NODE
int cari(struct all *s, int tNum){
    struct dot *curr = s->head;
    while(curr != NULL){
        if(curr->pass == tNum){
            return curr->total;
        }
        curr = curr -> next;    
    }
    return -1;
}

struct dot *createCust(int pass, char name[], int total){
    struct dot *newNode = (struct dot *)malloc(sizeof(struct dot));

    newNode -> pass = pass;
    strcpy(newNode -> name, name);
    newNode -> total = total;
    newNode -> next = NULL;

    return newNode;
}

void view(struct all *s){
    struct dot *curr = s->head;
    printf("========= ADMIN =========\n");
    while(curr != NULL){
        printf("%-20s %d\n", curr -> name, curr -> pass);
        curr = curr -> next;    
    }
}

// LIHAT
void lihat(struct all *s){
    struct dot *curr = s->head;
    while(curr != NULL){
        printf("[%s-%d] -> ", curr -> name, curr->pass);
        curr = curr -> next;    
    }
    printf("NULL\n");
}

// INSERT HEAD CUSTOMER
void insertHead1(struct all *s, int pass, char name[], int total){
    struct dot *newNode = createCust(pass, name, total);
    if(s->head == NULL){
        s->head = newNode;
        s->tail = newNode;
    }else{
        newNode -> next = s->head;
        s->head = newNode;
    }
}

// BIKIN NODE LINKED LIST
struct dot *createNewNode(int pass, char name[]){
    struct dot *newNode = (struct dot *)malloc(sizeof(struct dot));

    newNode -> pass = pass;
    strcpy(newNode -> name, name);
    newNode -> next = NULL;

    return newNode;
}

// INSERT HEAD LINKED LIST
void insertHead(struct all *s, int pass, char name[]){
    struct dot *newNode = createNewNode(pass, name);
    if(s->head == NULL){
        s->head = newNode;
        s->tail = newNode;
    }else{
        newNode -> next = s->head;
        s->head = newNode;
    }
}

// INSERT HEAD LINKED LIST CUSTOMER
void insertCust(struct all *s, int pass, char name[], int total){
    struct dot *newNode = createCust(pass, name, total);
    if(s->head == NULL){
        s->head = newNode;
        s->tail = newNode;
    }else{
        newNode -> next = s->head;
        s->head = newNode;
    }
}

// PRINT MAIN MENU
void mainMenu(){
	printf("|============================================|\n");
	printf("|         RUMAH MAKAN YANG MAU MAKAN         |\n");
	printf("|============================================|\n");
    printf("|1. Admin \t\t\t\t     |\n");
    printf("|2. Customer \t\t\t\t     |\n");
    printf("|0. Exit \t\t\t\t     |\n");
    printf("|============================================|\n");
    printf("=> ");
}

// PRINT ADMIN MENU
void menuAdmin(){
	printf("|============================================|\n");
	printf("|                  Menu Admin                |\n");
	printf("|============================================|\n");
    printf("|1. Tambah Menu \t\t\t     |\n"); // SUDAH
    printf("|2. Customer Log \t\t\t     |\n"); //SUDAH BUU
    printf("|3. Tambah Admin \t\t\t     |\n"); // SUDAH
    printf("|4. Delete Menu \t\t\t     |\n"); // SUDAH
    printf("|5. Delete Admin \t\t\t     |\n"); // SUDAH
    printf("|0. Return \t\t\t\t     |\n");
    printf("|============================================|\n");
    printf("=> ");
}

// PRINT CUSTOMER MENU
void menuCust(){
	printf("|============================================|\n");
	printf("|               Menu Customer                |\n");
	printf("|============================================|\n");
    printf("|1. Dine-in \t\t\t\t     |\n");
    printf("|2. Take-away \t\t\t\t     |\n");
    printf("|3. Payment \t\t\t\t     |\n");
    printf("|0. Return \t\t\t\t     |\n");
    printf("|============================================|\n");
    printf("=> ");
}

// MENU ORDER CUSTOMER
void custOrder(){
	printf("|============================================|\n");
	printf("|                    ORDER                   |\n");
	printf("|============================================|\n");
    printf("|1. Food \t\t\t\t     |\n"); // SUDAH
    printf("|2. Beverage \t\t\t\t     |\n"); // SUDAH
    printf("|0. Return \t\t\t\t     |\n");
    printf("|============================================|\n");
    printf("=> ");
}

// FUNGSI LOGIN UTAMA ADMIN
void loginAdmin(struct all* s, struct all *m, struct all *n){
    FILE *fp = fopen("admin.txt", "a+");
    int count = 0;
    char name[256];
    int pass, flag = 0, ch;
    printf("|===========================================|\n");
	printf("|                 Admin Menu                |\n");
	printf("|===========================================|\n");
    printf("Your name: ");
    scanf("%[^\n]s", name);getchar();
    printf("Password: ");
    scanf("%d", &pass);getchar();
    for(int i = 0; !feof(fp); i++){
        char tempName[256];
        int tempPass;
        fscanf(fp, "%[^#]#%d\n", tempName, &tempPass);
        insertHead(s, tempPass, tempName);
        count++;
    }
    fclose(fp);
    struct dot *curr = s->head;
    while(curr != NULL){
        if(strcmp(curr->name, name) == 0 && curr->pass == pass){ 
            flag = 1;
            break;
        }
        curr = curr -> next;    
    }
    cls
    if(flag == 1){
        menuAdmin();
        scanf("%d", &ch);getchar();
        switch(ch){
        	case 0: {
        		return;
				break;
			}
            case 1: {
                cls
                int ch, price;
                char food[256], beverage[256];
                printf("|============================================|\n");
				printf("|                 Tambah Menu                |\n");
				printf("|============================================|\n");
                printf("|1. Food \t\t\t\t     |\n");
                printf("|2. Beverage \t\t\t\t     |\n");
                printf("|0. Return \t\t\t\t     |\n");
                printf("|============================================|\n");
                printf("=> ");
                scanf("%d", &ch);getchar();
                while(ch != 0){
                    if(ch == 1){
                        FILE *fp1 = fopen("food.txt", "a");
                        printf("Food name: ");
                        scanf("%[^\n]", food);
                        printf("Food price: ");
                        scanf("%d", &price);getchar();
                        fprintf(fp1, "%s#%d\n", food, price);
                        fclose(fp1);
                        break;
                    }else if(ch == 2){
                        FILE *fp2 = fopen("beverage.txt", "a");
                        printf("Beverage Name: ");
                        scanf("%[^\n]s", beverage);getchar();
                        printf("Beverage price: ");
                        scanf("%d", &price);getchar();
                        fprintf(fp2, "%s#%d\n", beverage, price);
                        fclose(fp2);
                        break;
                    }else if(ch == 0){
                        break;
                    }else{
                        printf("Invalid input!\n");
                        etr
                        getchar();
                    }
                }
                break;
            }
            case 2: {
                cls
                FILE *fp = fopen("customerLog.txt", "r");
                printf("|============================================|\n");
				printf("|                Customer Log                |\n");
				printf("|============================================|\n");
                char name[256];
                int price, idx;
                for(int i=0;!feof(fp);i++){
                    fscanf(fp, "%[^#]#%d#%d\n", name, &price, &idx);
                    printf("%-15s %-10s %d\n", name, method[idx], price);
                }
                fclose(fp);
                break;
            }
            case 3: {
                cls
                char newName[256];
                int newPass;
                FILE *fp3 = fopen("admin.txt", "a");
                printf("|============================================|\n");
				printf("|                Add New Admin               |\n");
				printf("|============================================|\n");
                printf("New admin name: ");
                scanf("%[^\n]s", newName);getchar();
                printf("New admin password: ");
                scanf("%d", &newPass);getchar();
                fprintf(fp3, "%s#%d\n", newName, newPass);
                fclose(fp3);
                break;
            }
            case 4: {
                cls
                int ch, price;
                char food[256], beverage[256];
                printf("|============================================|\n");
				printf("|                 Delete Menu                |\n");
				printf("|============================================|\n");
                printf("|1. Food \t\t\t\t     |\n");
                printf("|2. Beverage \t\t\t\t     |\n");
                printf("|0. Return \t\t\t\t     |\n");
                printf("|============================================|\n");
                printf("=> ");
                scanf("%d", &ch);getchar();
                while(ch != 0){
                    if(ch == 1){
                        FILE *fptr = fopen("food.txt", "r");
                        for(int i=0;!feof(fptr); i++){
                            char nama[256];
                            int harga;
                            fscanf(fptr, "%[^#]#%d\n", nama, &harga);
                            insertHead(m, harga, nama);
                        }
                        fclose(fptr);
                        printf("Food u want to delete: ");
                        scanf("%[^\n]", food);getchar();
                        int x = deleteNodeName(m, food);
                        if(x == 0){
                            printf("There's no %s in the database!\n", food);
                            return;
                        }
                        struct dot *curr = m->head;
                        FILE *fptr1 = fopen("food.txt", "w");
                        while(curr != NULL){
                            fprintf(fptr, "%s#%d\n", curr->name, curr->pass);
                            curr = curr->next;
                        }
                        fclose(fptr1);
                        break;
                    }else if(ch == 2){
                        FILE *fptr = fopen("beverage.txt", "r");
                        for(int i=0;!feof(fptr); i++){
                            char nama[256];
                            int harga;
                            fscanf(fptr, "%[^#]#%d\n", nama, &harga);
                            insertHead(n, harga, nama);
                        }
                        fclose(fptr);
                        printf("Beverage u want to delete: ");
                        scanf("%[^\n]", beverage);getchar();
                        int x = deleteNodeName(n, beverage);
                        if(x == 0){
                            printf("There's no %s in the database!\n", beverage);
                            return;
                        }
                        struct dot *curr = n->head;
                        FILE *fptr1 = fopen("beverage.txt", "w");
                        while(curr != NULL){
                            fprintf(fptr, "%s#%d\n", curr->name, curr->pass);
                            curr = curr->next;
                        }
                        fclose(fptr1);
                        break;
                    }else if(ch == 0){
                        break;
                    }else{
                        printf("Invalid input!\n");
                        etr
                        getchar();
                    }
                }
                break;
            }
            case 5: {
                cls
                FILE *fp = fopen("admin.txt", "w+");
                int temp;
                char name[256];
                view(s);
                printf("Admin u want to delete: ");
                scanf("%[^\n]s", name);getchar();
                int x = deleteNodeName(s, name);
                if(x == 0){
                    printf("There's no %s in the database!\n", name);
                    return;
                }
                struct dot *curr = s->head; 
                while(curr != NULL){
                    fprintf(fp, "%s#%d\n", curr->name, curr->pass);
                    curr = curr->next;
                }                    
                fclose(fp);
                break;
            }
            default:{
            	printf("INVALID INPUT!\n");
            	etr
            	getchar();
				break;
			}
        }
    }else{
        printf("Wrong username or password, please try again!\n");
        etr
        getchar();
        getchar();
        return;
    }
    etr
    getchar();
}

// STRUCT TREE
struct node{
    int value;
    char name[256];
    struct node *left;
    struct node *right;
    int height;
};

// BIKIN NODE DI TREE
struct node *createTreeNode(int value, char name[]){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->value = value;
    strcpy(newNode->name, name);
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->height=0;

    return newNode;
}

// CARI MAX DARI 2 INTEGER
int max(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

// CARI HEIGHT TREE
int height(struct node *root){
    if(root == NULL){
        return -1;
    }else{
        return root->height;
    }
}

// ROTATE LEFT
struct node *rotateRight(struct node *root){
    struct node *y = root -> left;
    struct node *suby = y->right;

    y->right = root;
    root->left = suby;

    root->height = 1 + max(height(root->left), height(root->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// ROTATE RIGHT
struct node *rotateLeft(struct node *root){
    struct node *y = root -> right;
    struct node *suby = y->left;

    y->left = root;
    root->right = suby;

    root->height = 1 + max(height(root->left), height(root->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// INSERT TREE BERDASARKAN HARGA
struct node *insert(int value, struct node *root, char name[]){
    if(root == NULL){
        return createTreeNode(value, name);
    }else if(value > root->value){
        root->right = insert(value, root->right, name);
    }else{
        root->left = insert(value, root->left, name);
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = height(root->left) - height(root->right);
    if(balance > 1){
        if(value < root -> left -> value){
            return rotateRight(root);
        }else if(value > root -> left -> value){
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }else if(balance < -1){
        if(value > root -> right -> value){
            return rotateLeft(root);
        }else if(value < root -> right -> value){
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}

// INSERT TREE BERDASARKAN NAMA
struct node *insert2(int value, struct node *root, char name[]){
    if(root == NULL){
        return createTreeNode(value, name);
    }else if(strcmp(name, root->name) > 0){
        root->right = insert2(value, root->right, name);
    }else{
        root->left = insert2(value, root->left, name);
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = height(root->left) - height(root->right);
    if(balance > 1){
        if(strcmp(root->left->name, name) < 0){
            return rotateRight(root);
        }else if(strcmp(root->left->name, name) > 0){
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }else if(balance < -1){
        if(strcmp(name, root->right->name) > 0){
            return rotateLeft(root);
        }else if(strcmp(name, root->right->name) < 0){
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}

// PRINT DARI PALING KECIL
void printInOrder(struct node *root){
    if(root != NULL){
        printInOrder(root->left);
        printf("%-20s  %d\n", root->name, root->value);
        printInOrder(root->right);
    }
}

// SEARCHING DI TREE BERDASARKAN NAMA
int search(struct node* root, char name[]){
    if(root == NULL){
        printf("Couldn't find %s in the menu\n", name);
        return -1;
    }else{
        if(strcmp(root->name, name) == 0){
            return root->value;
        }
        if(strcmp(name, root->name)<0){
            return search(root->left, name);
        }else{
            return search(root->right, name);
        }
    }
}

// TRANSFER DARI TXT FILE KE TREE DAN MENGAMBIL ORDER CUSTOMER
int transfer(struct node *root1, struct node *root2){
    int pilih;
    char order[256];
    FILE *fp1 = fopen("food.txt", "r");
    FILE *fp2 = fopen("beverage.txt", "r");
    char fname[256], bname[256];
    int fprice, bprice;
    for(int i=0;!feof(fp1);i++){
        fscanf(fp1, "%[^#]#%d\n", fname, &fprice);
        root1 = insert2(fprice, root1, fname);
    }
    for(int i=0;!feof(fp2);i++){
        fscanf(fp2, "%[^#]#%d\n", bname, &bprice);
        root2 = insert2(bprice, root2, bname);
    }

    int total = 0;
    do{
    	cls
        custOrder();
        scanf("%d", &pilih);getchar();
        if(pilih != 0){
            if(pilih == 1){
                printf("         |===Food===|          \n");
                printf("|=============================|\n");
                printf("                              |\n");
                printInOrder(root1);
                printf("                              |\n");
                printf("|=============================|\n");
                printf("Your order: ");
                scanf("%[^\n]s", order);getchar();
                if(search(root1, order) != -1){
                    printf("%s = %d\n", order, search(root1, order));
                    int qty;
                    printf("Quantity: ");
                    scanf("%d", &qty);getchar();
                    for(int i = 0; i < qty; i++){
                        total += search(root1, order);
                    }
                }else{
                    printf("%s is not on the menu!\n", order);
                }
                etr
                getchar();
            }else if(pilih == 2){
                printf("       |===Beverage===|        \n");
                printf("|=============================|\n");
                printf("                              |\n");
                printInOrder(root2);
                printf("                              |\n");
                printf("|=============================|\n");
                printf("Your order: ");
                scanf("%[^\n]s", order);getchar();
                if(search(root2, order) != -1){
                    printf("%s = %d\n", order, search(root2, order));
                    total += search(root2, order);
                }else{
                    printf("%s is not on the menu!\n", order);
                    int qty;
                    printf("Quantity: ");
                    scanf("%d", &qty);getchar();
                    for(int i = 0; i < qty; i++){
                        total += search(root1, order);
                    }
                }
                etr
                getchar();
            }
        	else{
        		printf("INVALID INPUT!\n");
        		etr
        		getchar();
			}
        }
    }while(pilih != 0);
    
    return total;
}

// CARI APAKAH RESTORAN PENUH, JIKA TIDAK MAKA AKAN PRINT SEMUA MEJA YANG TERSEDIA
void takeAway(struct all *s){
    struct dot *curr = s->head;
    if(curr == NULL){
        printf("\n\nAll table is available!(1-10)\n");
    }else{
        printf("\n\nOccupied tables: ");
        while(curr != NULL){
            printf("[%d] -> ", curr->pass);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

// CEK APAKAH MEJA YANG INGIN PELANGGAN TEMPATI SUDAH PENUH ATAU BELUM
int cek(struct all *s, int value){
    int flag = 0, count = 0;
    struct dot *curr = s->head;
    while(curr != NULL){
        count++;
        if(curr->pass == value){
            flag = 1;
            return flag;
        }
        curr = curr->next;
    }
    if(count == 10){
        return count;
    }
    return flag;
}

// FUNGSI UTAMA ORDER
void order(struct all *meja, struct all *cust){
    FILE *fp = fopen("customerLog.txt", "a");
    menuCust();
    int ch;
    scanf("%d", &ch);getchar();
    struct node *root1 = NULL, *root2 = NULL;
    switch(ch){
        case 1: {
            struct dot *s;
            int c = -1;
            char name[256], order[256];
            if(cek(meja, c) == 10){
                printf("We're sorry, our restaurant is full rn!\n");
                return;
            }
            printf("What's your name: ");
            scanf("%[^\n]", name);
            takeAway(meja);
            mejas:
            printf("Which table do you want(1-10): ");
            scanf("%d", &c);getchar();
            if(c <= 10 && c >= 1){
                if(cek(meja, c) == 1){
                    printf("The table you want is already occupied!\n");
                    return;
                }
                insertHead(meja, c, name);
            }else{
                printf("Invalid input!\n");
                etr
                getchar();
                goto mejas;
            }
            int total = transfer(root1, root2);
            insertHead1(cust, c, name, total);
            printf("Your current total is %d\n", total);
            etr
            getchar();
            break;
        }
        case 2: {
            struct dot *s;
            int c = -1, ch;
            char name[256], order[256];
            printf("What's your name: ");
            scanf("%[^\n]", name);
            int total = transfer(root1, root2);
            printf("Your current total is %d\n", total);
            printf("|============================================|\n");
            printf("|What payment method do u want to use?       |\n");
            printf("|1. Cash \t\t\t\t     |\n");
            printf("|2. Cashless \t\t\t\t     |\n");
            printf("|0. Return \t\t\t\t     |\n");
            printf("|============================================|\n");
            printf("=> ");
            scanf("%d", &ch);getchar();
            switch(ch){
                case 1: {
                    printf("Your total is %d\n", total);
                    fprintf(fp, "%s#%d#%d\n", name, total, ch-1);
                    printf("Your payment is successfull\n");
                    etr
                    getchar();
                    break;
                }

                case 2: {
                    printf("Your total is %d (Cashless fee = 2500)\n", total+2500);
                    fprintf(fp, "%s#%d#%d\n", name, total+2500, ch-1);
                    printf("Your payment is successfull\n");
                    etr
                    getchar();
                    break;
                }

                case 0: {
                    return;
                }

                default: {
                    printf("Invalid input\n");
                    break;
                }
            }
            fclose(fp);
            break;
        }
        case 3: {
            int c = -1;
            char name[256];
            int tNum;
            printf("What's your name: ");
            scanf("%[^\n]", name);getchar();
            printf("What's your table number: ");
            scanf("%d", &tNum);getchar();
            int total = cari(cust, tNum);
            if(total == -1){
                printf("There's no order at table number %d!\n", tNum);
                etr
                getchar();
                break;
            }
            printf("|============================================|\n");
            printf("|What payment method do u want to use?       |\n");
            printf("|1. Cash \t\t\t\t     |\n");
            printf("|2. Cashless \t\t\t\t     |\n");
            printf("|0. Return \t\t\t\t     |\n");
            printf("|============================================|\n");
            printf("=> ");
            scanf("%d", &ch);getchar();
            switch(ch){
                case 1: {
                    fprintf(fp, "%s#%d#%d\n", name, total, ch-1);
                    printf("Your total is %d\n", total);
                    printf("Your payment is successfull\n");
                    deleteNodeTable(cust, tNum);
                    deleteNodeTable(meja, tNum);
                    etr
                    getchar();
                    break;
                }

                case 2: {
                    printf("Your total is %d\n", total+2500);
                    fprintf(fp, "%s#%d#%d\n", name, total+2500, ch-1);
                    printf("Your payment is successfull\n");
                    deleteNodeTable(cust, tNum);
                    deleteNodeTable(meja, tNum);
                    etr
                    getchar();
                    break;
                }

                case 0: {
                    return;
                }

                default: {
                    printf("Invalid input\n");
                    break;
                }
            }
            fclose(fp);
            break;
        }
        case 0: {
            return;
        }
        default: {
            printf("Invalid input!\n");
            break;
        }
    }
}

// INT MAIN
int main(){
    cls
    time_t t1;
    srand ((unsigned) time (&t1));

    struct all *customer = newList();
    struct all *meja = newList();

    int ch;
    char name[255], password[15];
    do{ 
    	cls
        mainMenu();
        scanf("%d", &ch);getchar();
        switch(ch){
            case 1: {
                cls
                struct all *admin = newList();
                struct all *food = newList();
                struct all *beverage = newList();
                loginAdmin(admin, food, beverage);
                free(admin);
                break;
            }
            case 2: {
                cls
                order(meja, customer);
                break;
            }  
            case 0: {
                cls
                printf("Thank's for using our program!\n");
                break;
            }
            default: {
                cls
                etr
                getchar();
                break;
            }
        }   
    }while(ch != 0);

    return 0;
}
