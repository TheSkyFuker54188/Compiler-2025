@arr = global [6 x i32] [i32 1,i32 2,i32 33,i32 4,i32 5,i32 6]
define i32 @main()
{
L1:  
    %r7 = load i32, ptr %r6
    %r10 = icmp slt i32 %r7,%r8
    br i1 %r10, label %L1, label %L2
    %r7 = getelementptr [6 x i32], ptr @arr, i32 0, i32 %r6
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r8,%r8
    store i32 0, ptr %r8
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    br label %L1
L2:  
L3:  
    ret i32 6
}
