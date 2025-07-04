define float @reverse(i32 %r0)
{
L1:  
    %r5 = call float @getint()
    store i32 %r5, ptr %r1
    %r2 = call float @putint(i32 %r1)
    br label %L2
    %r3 = call float @getint()
    store i32 %r3, ptr %r1
    %r1 = load i32, ptr %r0
    %r4 = sub i32 %r1,%r2
    %r5 = call float @reverse(float %r4)
    %r2 = call float @putint(i32 %r1)
    br label %L2
L2:  
L3:  
}
define i32 @main()
{
L1:  
    %r3 = alloca i32
    store i32 200, ptr %r3
    %r4 = call i32 @reverse(i32 %r3)
    ret i32 0
}
