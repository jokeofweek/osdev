size_t strlen(const u8int *str){
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}

int strcmp(const u8int *str1, const u8int *str2){

     u8int uc1, uc2;
     /* Move str1 and str2 to the first differing u8intacters 
        in each string, or the ends of the strings if they
        are identical.  */
     while (*str1 != '\0' && *str1 == *str2) {
         str1++;
         str2++;
     }
     /* Compare the u8intacters as u8int and
        return the difference.  */
     uc1 = (*(u8int *) str1);
     uc2 = (*(u8int *) str2);
     return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}
