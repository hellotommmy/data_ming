#include "head.h"
void test_make_node();
void test_make_list();
void test_delete_node();
void generate_SD();
//no light medium heavy

char *cong_level_set[4] = {"n","l","m","h"};
int main(){
    generate_SD();
	freq_episode_mining();

    return 0;
}
