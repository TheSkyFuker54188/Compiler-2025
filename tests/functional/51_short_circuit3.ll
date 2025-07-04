@a = global i32 zeroinitializer
@b = global i32 zeroinitializer
@d = global i32 zeroinitializer
define i32 @set_a(i32 %r0)
{
L1:  
    %r1 = load i32, ptr @a
    store i32 %r0, ptr %r1
    %r2 = load i32, ptr @a
    ret i32 %r2
}
define i32 @set_b(i32 %r0)
{
L1:  
    %r4 = load i32, ptr @b
    store i32 %r3, ptr %r4
    %r5 = load i32, ptr @b
    ret i32 %r5
}
define i32 @set_d(i32 %r0)
{
L1:  
    %r7 = load i32, ptr @d
    store i32 %r6, ptr %r7
    %r8 = load i32, ptr @d
    ret i32 %r8
}
define i32 @main()
{
L1:  
    br label %L2
L3:  
    %r20 = load i32, ptr @a
    %r21 = call i32 @putint(i32 %r20)
    %r23 = call i32 @putch(i32 %r22)
    %r24 = load i32, ptr @b
    %r25 = call i32 @putint(i32 %r24)
    %r27 = call i32 @putch(i32 %r26)
    %r29 = load i32, ptr @a
    store i32 2, ptr %r29
    %r31 = load i32, ptr @b
    store i32 3, ptr %r31
    %r33 = call i32 @set_a(i32 %r32)
    %r34 = load float, ptr %r33
    %r36 = call i32 @set_b(i32 %r35)
    %r37 = load float, ptr %r36
    %r38 = and i32 %r34,%r37
    br i1 %r38, label %L3, label %L4
    br label %L5
L4:  
L6:  
    %r47 = alloca i32
    %r39 = load i32, ptr @a
    %r40 = call i32 @putint(i32 %r39)
    %r42 = call i32 @putch(i32 %r41)
    %r43 = load i32, ptr @b
    %r44 = call i32 @putint(i32 %r43)
    %r46 = call i32 @putch(i32 %r45)
    store i32 1, ptr %r47
    %r50 = load i32, ptr @d
    store i32 2, ptr %r50
    %r48 = load i32, ptr %r47
    %r51 = icmp sge i32 %r48,%r49
    %r52 = load float, ptr %r51
    %r54 = call i32 @set_d(i32 %r53)
    %r55 = load float, ptr %r54
    %r56 = and i32 %r52,%r55
    br i1 %r56, label %L6, label %L7
    br label %L8
L7:  
L9:  
    %r57 = load i32, ptr @d
    %r58 = call i32 @putint(i32 %r57)
    %r60 = call i32 @putch(i32 %r59)
    %r48 = load i32, ptr %r47
    %r51 = icmp sle i32 %r48,%r49
    %r52 = load float, ptr %r51
    %r54 = call i32 @set_d(i32 %r53)
    %r55 = load float, ptr %r54
    %r56 = xor i32 %r52,%r55
    br i1 %r56, label %L9, label %L10
    br label %L11
L10:  
L12:  
    %r57 = load i32, ptr @d
    %r58 = call i32 @putint(i32 %r57)
    %r60 = call i32 @putch(i32 %r59)
    %r69 = add i32 %r65,%r67
    %r70 = load float, ptr %r69
    %r71 = sub i32 %r63,%r70
    %r72 = load float, ptr %r71
    %r73 = icmp sge i32 %r61,%r72
    br i1 %r73, label %L12, label %L13
    %r75 = call i32 @putch(i32 %r74)
    br label %L14
L13:  
L15:  
    %r80 = sub i32 %r76,%r78
    %r81 = load float, ptr %r80
    %r88 = mul i32 %r84,%r86
    %r89 = load float, ptr %r88
    %r90 = sub i32 %r82,%r89
    %r91 = load float, ptr %r90
    %r92 = icmp ne i32 %r81,%r91
    br i1 %r92, label %L15, label %L16
    %r94 = call i32 @putch(i32 %r93)
    br label %L17
L16:  
L18:  
    %r99 = icmp slt i32 %r95,%r97
    %r100 = load float, ptr %r99
    %r105 = srem i32 %r101,%r103
    %r106 = load float, ptr %r105
    %r107 = icmp ne i32 %r100,%r106
    br i1 %r107, label %L18, label %L19
    %r109 = call i32 @putch(i32 %r108)
    br label %L20
L19:  
L21:  
    %r114 = icmp sgt i32 %r110,%r112
    %r115 = load float, ptr %r114
    %r118 = icmp eq i32 %r115,%r116
    br i1 %r118, label %L21, label %L22
    %r120 = call i32 @putch(i32 %r119)
    br label %L23
L22:  
L24:  
    %r127 = icmp sle i32 %r123,%r125
    %r128 = load float, ptr %r127
    %r129 = icmp eq i32 %r121,%r128
    br i1 %r129, label %L24, label %L25
    %r131 = call i32 @putch(i32 %r130)
    br label %L26
L25:  
L27:  
    %r136 = sub i32 %r132,%r134
    %r137 = load float, ptr %r136
    %r139 = icmp eq i32 %r138,%r0
    %r140 = sub i32 %r0,%r139
    %r141 = load float, ptr %r140
    %r142 = icmp eq i32 %r137,%r141
    br i1 %r142, label %L27, label %L28
    %r144 = call i32 @putch(i32 %r143)
    br label %L29
L28:  
L30:  
    %r155 = alloca i32
    %r153 = alloca i32
    %r151 = alloca i32
    %r149 = alloca i32
    %r147 = alloca i32
    %r146 = call i32 @putch(i32 %r145)
    store i32 0, ptr %r147
    store i32 1, ptr %r149
    store i32 2, ptr %r151
    store i32 3, ptr %r153
    store i32 4, ptr %r155
    br label %L30
    %r148 = load i32, ptr %r147
    %r150 = load i32, ptr %r149
    %r151 = and i32 %r148,%r150
    br i1 %r151, label %L31, label %L32
    %r153 = call i32 @putch(i32 %r152)
    br label %L31
L31:  
L32:  
L33:  
    %r148 = load i32, ptr %r147
    %r150 = load i32, ptr %r149
    %r151 = xor i32 %r148,%r150
    br i1 %r151, label %L33, label %L34
    %r153 = call i32 @putch(i32 %r152)
    br label %L35
L34:  
L36:  
    %r148 = load i32, ptr %r147
    %r150 = load i32, ptr %r149
    %r151 = icmp sge i32 %r148,%r150
    %r152 = load i32, ptr %r151
    %r150 = load i32, ptr %r149
    %r148 = load i32, ptr %r147
    %r149 = icmp sle i32 %r150,%r148
    %r150 = load i32, ptr %r149
    %r151 = xor i32 %r152,%r150
    br i1 %r151, label %L36, label %L37
    %r153 = call i32 @putch(i32 %r152)
    br label %L38
L37:  
L39:  
    %r152 = load i32, ptr %r151
    %r150 = load i32, ptr %r149
    %r151 = icmp sge i32 %r152,%r150
    %r152 = load i32, ptr %r151
    %r156 = load i32, ptr %r155
    %r154 = load i32, ptr %r153
    %r155 = icmp ne i32 %r156,%r154
    %r156 = load i32, ptr %r155
    %r157 = and i32 %r152,%r156
    br i1 %r157, label %L39, label %L40
    %r159 = call i32 @putch(i32 %r158)
    br label %L41
L40:  
L42:  
    %r148 = load i32, ptr %r147
    %r150 = icmp eq i32 %r149,%r0
    %r152 = icmp eq i32 %r148,%r150
    %r154 = load i32, ptr %r153
    %r154 = load i32, ptr %r153
    %r155 = icmp slt i32 %r154,%r154
    %r156 = load i32, ptr %r155
    %r157 = and i32 %r152,%r156
    %r158 = load float, ptr %r157
    %r156 = load i32, ptr %r155
    %r156 = load i32, ptr %r155
    %r157 = icmp sge i32 %r156,%r156
    %r158 = load float, ptr %r157
    %r159 = xor i32 %r158,%r158
    br i1 %r159, label %L42, label %L43
    %r161 = call i32 @putch(i32 %r160)
    br label %L44
L43:  
L45:  
    %r148 = load i32, ptr %r147
    %r150 = icmp eq i32 %r149,%r0
    %r152 = icmp eq i32 %r148,%r150
    %r154 = load i32, ptr %r153
    %r154 = load i32, ptr %r153
    %r155 = icmp slt i32 %r154,%r154
    %r156 = load i32, ptr %r155
    %r156 = load i32, ptr %r155
    %r156 = load i32, ptr %r155
    %r157 = icmp sge i32 %r156,%r156
    %r158 = load float, ptr %r157
    %r159 = and i32 %r156,%r158
    %r160 = load float, ptr %r159
    %r161 = xor i32 %r152,%r160
    br i1 %r161, label %L45, label %L46
    %r163 = call i32 @putch(i32 %r162)
    br label %L47
L46:  
L48:  
    %r165 = call i32 @putch(i32 %r164)
    ret i32 0
}
