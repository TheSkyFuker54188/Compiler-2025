define i32 @main()
{
L1:  
    %r6 = sub i32 %r0,%r5
    %r7 = sub i32 %r0,%r6
    %r8 = sub i32 %r0,%r7
    store i32 %r8, ptr %r0
    br label %L2
    store i32 10, ptr %r0
    br label %L2
L2:  
L3:  
    ret i32 %r0
}
