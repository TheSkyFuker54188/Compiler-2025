@a = global [5 x i32] [i32 0,i32 1,i32 2,i32 3,i32 4]
define i32 @main()
{
L1:  
    %r6 = getelementptr [5 x i32], ptr @a, i32 0, i32 %r5
    ret i32 %r6
}
