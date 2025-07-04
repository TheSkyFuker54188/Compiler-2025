define i32 @main()
{
L1:  
    %r6 = sub i32 %r0,%r5
    %r7 = sub i32 %r0,%r6
    %r8 = sub i32 %r0,%r7
    store i32 %r8, ptr %r0
    br label %L2
    %r3 = add i32 %r1,%r1
    store i32 %r3, ptr %r0
    br label %L2
L2:  
L3:  
    %r1 = call i32 @putint(i32 %r0)
    ret i32 56
}
