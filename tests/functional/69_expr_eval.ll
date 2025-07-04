@TOKEN_NUM = global i32 0
@TOKEN_OTHER = global i32 1
@last_char = global i32 32
@num = global i32 zeroinitializer
@other = global i32 zeroinitializer
@cur_token = global i32 zeroinitializer
define i32 @next_char()
{
L1:  
    %r3 = call i32 @getch()
    %r4 = load i32, ptr @last_char
    store i32 %r3, ptr %r4
    %r5 = load i32, ptr @last_char
    ret i32 %r5
}
define i32 @next_token()
{
L1:  
    br label %L6
    %r24 = load i32, ptr @last_char
    %r25 = call i32 @is_space(i32 %r24)
    br i1 %r25, label %L7, label %L8
    %r26 = call i32 @next_char()
    br label %L7
L7:  
L8:  
L9:  
    %r27 = load i32, ptr @last_char
    %r28 = call i32 @is_num(i32 %r27)
    br i1 %r28, label %L9, label %L10
    %r29 = load i32, ptr @last_char
    %r30 = load i32, ptr %r29
    %r33 = sub i32 %r30,%r31
    %r34 = load i32, ptr @num
    store i32 %r33, ptr %r34
    br label %L12
    %r35 = call i32 @next_char()
    %r36 = call i32 @is_num(float %r35)
    br i1 %r36, label %L13, label %L14
    %r37 = load i32, ptr @num
    %r38 = load i32, ptr %r37
    %r41 = mul i32 %r38,%r39
    %r42 = load float, ptr %r41
    %r43 = load i32, ptr @last_char
    %r44 = load i32, ptr %r43
    %r45 = add i32 %r42,%r44
    %r46 = load float, ptr %r45
    %r49 = sub i32 %r46,%r47
    %r50 = load i32, ptr @num
    store i32 %r49, ptr %r50
    br label %L13
L10:  
L11:  
L12:  
    %r58 = load i32, ptr @cur_token
    ret i32 %r58
L13:  
L14:  
L15:  
    %r52 = load i32, ptr @cur_token
    store i32 0, ptr %r52
    br label %L11
    %r53 = load i32, ptr @last_char
    %r54 = load i32, ptr @other
    store i32 %r53, ptr %r54
    %r55 = call i32 @next_char()
    %r57 = load i32, ptr @cur_token
    store i32 1, ptr %r57
    br label %L11
}
define i32 @is_space(i32 %r0)
{
L1:  
    ret i32 1
    br label %L2
    ret i32 0
    br label %L2
L2:  
L3:  
}
define i32 @is_num(i32 %r0)
{
L1:  
    %r16 = load i32, ptr %r15
    %r19 = icmp sge i32 %r16,%r17
    %r20 = load float, ptr %r19
    %r16 = load i32, ptr %r15
    %r19 = icmp sle i32 %r16,%r17
    %r20 = load float, ptr %r19
    %r21 = and i32 %r20,%r20
    br i1 %r21, label %L3, label %L4
    ret i32 1
    br label %L5
    ret i32 0
    br label %L5
L4:  
L5:  
L6:  
}
define i32 @panic()
{
L1:  
    %r60 = call i32 @putch(i32 %r59)
    %r62 = call i32 @putch(i32 %r61)
    %r64 = call i32 @putch(i32 %r63)
    %r66 = call i32 @putch(i32 %r65)
    %r68 = call i32 @putch(i32 %r67)
    %r70 = call i32 @putch(i32 %r69)
    %r72 = call i32 @putch(i32 %r71)
    %r74 = sub i32 %r0,%r73
    ret i32 %r74
}
define i32 @get_op_prec(i32 %r0)
{
L1:  
    %r76 = load i32, ptr %r75
    %r79 = icmp eq i32 %r76,%r77
    %r80 = load float, ptr %r79
    %r76 = load i32, ptr %r75
    %r79 = icmp eq i32 %r76,%r77
    %r80 = load float, ptr %r79
    %r81 = xor i32 %r80,%r80
    br i1 %r81, label %L15, label %L16
    ret i32 10
    br label %L17
L16:  
L18:  
    %r76 = load i32, ptr %r75
    %r79 = icmp eq i32 %r76,%r77
    %r80 = load float, ptr %r79
    %r76 = load i32, ptr %r75
    %r79 = icmp eq i32 %r76,%r77
    %r80 = load float, ptr %r79
    %r81 = xor i32 %r80,%r80
    %r82 = load float, ptr %r81
    %r76 = load i32, ptr %r75
    %r79 = icmp eq i32 %r76,%r77
    %r80 = load float, ptr %r79
    %r81 = xor i32 %r82,%r80
    br i1 %r81, label %L18, label %L19
    ret i32 10
    br label %L20
L19:  
L21:  
    ret i32 0
}
define float @stack_push(i32 %r0,i32 %r84)
{
L1:  
    %r87 = getelementptr [0 x i32], ptr %r84, i32 0, i32 %r86
    %r88 = load float, ptr %r87
    %r91 = add i32 %r88,%r89
    %r93 = getelementptr [0 x i32], ptr %r84, i32 0, i32 %r92
    store float %r91, ptr %r93
    %r87 = getelementptr [0 x i32], ptr %r84, i32 0, i32 %r86
    %r88 = getelementptr [0 x i32], ptr %r84, i32 0, i32 %r87
    store float %r85, ptr %r88
}
define i32 @stack_pop(i32 %r0)
{
L1:  
    %r90 = alloca i32
    %r92 = getelementptr [0 x i32], ptr %r89, i32 0, i32 %r91
    %r93 = getelementptr [0 x i32], ptr %r89, i32 0, i32 %r92
    store i32 %r93, ptr %r90
    %r95 = getelementptr [0 x i32], ptr %r89, i32 0, i32 %r94
    %r96 = load float, ptr %r95
    %r99 = sub i32 %r96,%r97
    %r101 = getelementptr [0 x i32], ptr %r89, i32 0, i32 %r100
    store float %r99, ptr %r101
    ret i32 %r90
}
define i32 @stack_peek(i32 %r0)
{
L1:  
    %r93 = getelementptr [0 x i32], ptr %r91, i32 0, i32 %r92
    %r94 = getelementptr [0 x i32], ptr %r91, i32 0, i32 %r93
    ret i32 0
}
define i32 @stack_size(i32 %r0)
{
L1:  
    %r97 = getelementptr [0 x i32], ptr %r95, i32 0, i32 %r96
    ret i32 1
}
define i32 @eval_op(i32 %r0,i32 %r98,i32 %r2)
{
L1:  
    %r99 = load i32, ptr %r98
    %r102 = icmp eq i32 %r99,%r100
    br i1 %r102, label %L21, label %L22
    %r100 = load i32, ptr %r99
    %r102 = add i32 %r100,%r100
    ret i32 %r102
    br label %L23
L22:  
L24:  
    %r99 = load i32, ptr %r98
    %r102 = icmp eq i32 %r99,%r100
    br i1 %r102, label %L24, label %L25
    %r100 = load i32, ptr %r99
    %r102 = sub i32 %r100,%r100
    ret i32 %r102
    br label %L26
L25:  
L27:  
    %r99 = load i32, ptr %r98
    %r102 = icmp eq i32 %r99,%r100
    br i1 %r102, label %L27, label %L28
    %r100 = load i32, ptr %r99
    %r102 = mul i32 %r100,%r100
    ret i32 %r102
    br label %L29
L28:  
L30:  
    %r99 = load i32, ptr %r98
    %r102 = icmp eq i32 %r99,%r100
    br i1 %r102, label %L30, label %L31
    %r100 = load i32, ptr %r99
    %r102 = sdiv i32 %r100,%r100
    ret i32 %r102
    br label %L32
L31:  
L33:  
    %r99 = load i32, ptr %r98
    %r102 = icmp eq i32 %r99,%r100
    br i1 %r102, label %L33, label %L34
    %r100 = load i32, ptr %r99
    %r102 = srem i32 %r100,%r100
    ret i32 %r102
    br label %L35
L34:  
L36:  
    ret i32 0
}
define i32 @eval()
{
L1:  
    %r105 = alloca [256 x i32]
    %r104 = alloca [256 x i32]
    %r106 = load i32, ptr @cur_token
    %r107 = load i32, ptr %r106
    %r110 = icmp ne i32 %r107,%r108
    br i1 %r110, label %L36, label %L37
    %r111 = call i32 @panic()
    ret i32 %r111
    br label %L38
L37:  
L39:  
    %r113 = alloca i32
    %r105 = load i32, ptr @num
    %r106 = call i32 @stack_push(i32 %r104,i32 %r105)
    %r107 = call i32 @next_token()
    br label %L39
    %r108 = load i32, ptr @cur_token
    %r109 = load i32, ptr %r108
    %r112 = icmp eq i32 %r109,%r110
    br i1 %r112, label %L40, label %L41
    %r114 = load i32, ptr @other
    store i32 %r114, ptr %r113
    %r114 = call i32 @get_op_prec(i32 %r113)
    %r115 = icmp eq i32 %r114,%r0
    br i1 %r115, label %L42, label %L43
    br label %L41
    br label %L44
L40:  
L41:  
L42:  
    %r106 = alloca i32
    %r107 = alloca i32
    %r107 = alloca i32
    %r108 = call i32 @next_token()
    br label %L51
    %r106 = call i32 @stack_size(i32 %r105)
    br i1 %r106, label %L52, label %L53
    %r106 = call i32 @stack_pop(i32 %r105)
    store i32 %r106, ptr %r107
    %r105 = call i32 @stack_pop(i32 %r104)
    store i32 %r105, ptr %r107
    %r105 = call i32 @stack_pop(i32 %r104)
    store i32 %r105, ptr %r106
    %r108 = call i32 @eval_op(i32 %r107,i32 %r106,i32 %r107)
    %r109 = call i32 @stack_push(i32 %r104,i32 %r108)
    br label %L52
L43:  
L45:  
    %r106 = alloca i32
    %r107 = alloca i32
    %r119 = alloca i32
    %r116 = call i32 @next_token()
    br label %L45
    %r106 = call i32 @stack_size(i32 %r105)
    %r107 = load i32, ptr %r106
    %r106 = call i32 @stack_peek(i32 %r105)
    %r107 = call i32 @get_op_prec(i32 %r106)
    %r108 = load float, ptr %r107
    %r114 = call i32 @get_op_prec(i32 %r113)
    %r115 = load i32, ptr %r114
    %r116 = icmp sge i32 %r108,%r115
    %r117 = load float, ptr %r116
    %r118 = and i32 %r107,%r117
    br i1 %r118, label %L46, label %L47
    %r106 = call i32 @stack_pop(i32 %r105)
    store i32 %r106, ptr %r119
    %r105 = call i32 @stack_pop(i32 %r104)
    store i32 %r105, ptr %r107
    %r105 = call i32 @stack_pop(i32 %r104)
    store i32 %r105, ptr %r106
    %r108 = call i32 @eval_op(i32 %r119,i32 %r106,i32 %r107)
    %r109 = call i32 @stack_push(i32 %r104,i32 %r108)
    br label %L46
L46:  
L47:  
L48:  
    %r114 = call i32 @stack_push(i32 %r105,i32 %r113)
    %r115 = load i32, ptr @cur_token
    %r116 = load i32, ptr %r115
    %r119 = icmp ne i32 %r116,%r117
    br i1 %r119, label %L48, label %L49
    %r120 = call i32 @panic()
    ret i32 %r120
    br label %L50
L49:  
L51:  
    %r105 = load i32, ptr @num
    %r106 = call i32 @stack_push(i32 %r104,i32 %r105)
    %r107 = call i32 @next_token()
    br label %L40
L52:  
L53:  
L54:  
    %r105 = call i32 @stack_peek(i32 %r104)
    ret i32 %r105
}
define i32 @main()
{
L1:  
    %r106 = alloca i32
    %r107 = call i32 @getint()
    store i32 %r107, ptr %r106
    %r108 = call i32 @getch()
    %r109 = call i32 @next_token()
    br label %L54
    br i1 %r106, label %L55, label %L56
    %r107 = call i32 @eval()
    %r108 = call i32 @putint(i32 %r107)
    %r110 = call i32 @putch(i32 %r109)
    %r107 = load i32, ptr %r106
    %r110 = sub i32 %r107,%r108
    store i32 1, ptr %r106
    br label %L55
L55:  
L56:  
L57:  
    ret i32 0
}
