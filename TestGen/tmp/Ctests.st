Ctests(imports, KATtests, testNames) ::= <<
#include \<string.h>
#include \<stdlib.h>
#include \<stdio.h>
<imports:{import | #include "<import>"}; separator="\n">

int compare_results(unsigned char *res1, unsigned char *res2, int length)
{
	int i;
	for(i=0; i\<length; i++)
	{
		if(res1[i]!=res2[i]){
			return 0;
		}
	}
	return 1;
}

int check_KAT(unsigned char *result,
        unsigned char *expected_result, int length,
        unsigned char *testname){
	if(!compare_results(result, expected_result, length)){
		printf("%s failed!\n",testname);
		return 1;
	}
	return 0;
}

<KATtests>

int main(){
	<testNames:{n | <n>();}; separator="\n">
	
	return 1;
}

>>