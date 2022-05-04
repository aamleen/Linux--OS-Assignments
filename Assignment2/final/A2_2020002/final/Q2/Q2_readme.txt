Required diff: kernel_2d_memcpy

Program logic:
	Starting with, I had opened the sys.c that contains the systemcall definitions and is located in build/linux-5.14.4/kernel . Here, I added a new system-call SYSCALL_DEFINE4, which means that I will be taking 4 parameters as input. These will be the row and column of the matrix and 2 matrices too.
  Then I create a temporary 1D array in kernel space and then in a loop, which loops over every row in the matrix, I copy each row from the given matrix(in user space) to the temporary created row-matrix. Then I copy the same row from the temp row-matrix to the 2nd matrix(in user space). This is repeated for each row, and in every iteration the temp row-matrix is overwritten with a new row. Then I write in the kernel log using printk to register that the matrix has been copie successfully.
   2nd step was to make this system call visible in the table containing all the definitions only, which is located in build/linux-5.14.4/arch/x86/entry/syscalls/syscall_64.tbl I edited this table and placed the syscall kernel_2d_memcpy on 448th no. 
   Then the kernel was compiled and all the necessary modules were installed after which the required images were moved to the required directories and then a reboot was made to login the new customised kernel.
   When the test was executed with ./test, the result was sucessful as a matrix was copied on to a blank matrix. This was verified by printing both matrices and also checking the kernel log using sudo dmesg|tail.

test.c logic:
	In the test file I have just created a custom matrix, passed it to the kernel_2d_memcpy syscall and got the desired result.

Regarding the patch:
   I am not very familiar with patches and all, so as mentioned by Arani sir in email, I had created a diff/patch of only the changes I made in sys.c and syscall_64.tbl .This diff is with the name kernel_2d_memcpy. The other one also includes the config file we were made to change. 