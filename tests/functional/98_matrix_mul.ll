@M = global i32 zeroinitializer
@L = global i32 zeroinitializer
@N = global i32 zeroinitializer
define i32 @mul(void %r0,void %r0,void %r2,void %r1,void %r4,void %r2,void %r6,void %r3,void %r8)
{
L1:  
    %r9 = alloca i32
    store i32 0, ptr %r9
    %r11 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r10
    %r12 = load float, ptr %r11
    %r14 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r13
    %r15 = load float, ptr %r14
    %r16 = mul i32 %r12,%r15
    %r17 = load float, ptr %r16
    %r19 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r18
    %r20 = load float, ptr %r19
    %r22 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r21
    %r23 = load float, ptr %r22
    %r24 = mul i32 %r20,%r23
    %r25 = load float, ptr %r24
    %r26 = add i32 %r17,%r25
    %r27 = load float, ptr %r26
    %r29 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r28
    %r30 = load float, ptr %r29
    %r32 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r31
    %r33 = load float, ptr %r32
    %r34 = mul i32 %r30,%r33
    %r35 = load float, ptr %r34
    %r36 = add i32 %r27,%r35
    %r38 = getelementptr [0 x void], ptr %r6, i32 0, i32 %r37
    store float %r36, ptr %r38
    %r40 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r39
    %r41 = load float, ptr %r40
    %r43 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r42
    %r44 = load float, ptr %r43
    %r45 = mul i32 %r41,%r44
    %r46 = load float, ptr %r45
    %r48 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r47
    %r49 = load float, ptr %r48
    %r51 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r50
    %r52 = load float, ptr %r51
    %r53 = mul i32 %r49,%r52
    %r54 = load float, ptr %r53
    %r55 = add i32 %r46,%r54
    %r56 = load float, ptr %r55
    %r58 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r57
    %r59 = load float, ptr %r58
    %r61 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r60
    %r62 = load float, ptr %r61
    %r63 = mul i32 %r59,%r62
    %r64 = load float, ptr %r63
    %r65 = add i32 %r56,%r64
    %r67 = getelementptr [0 x void], ptr %r6, i32 0, i32 %r66
    store float %r65, ptr %r67
    %r69 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r68
    %r70 = load float, ptr %r69
    %r72 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r71
    %r73 = load float, ptr %r72
    %r74 = mul i32 %r70,%r73
    %r75 = load float, ptr %r74
    %r77 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r76
    %r78 = load float, ptr %r77
    %r80 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r79
    %r81 = load float, ptr %r80
    %r82 = mul i32 %r78,%r81
    %r83 = load float, ptr %r82
    %r84 = add i32 %r75,%r83
    %r85 = load float, ptr %r84
    %r87 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r86
    %r88 = load float, ptr %r87
    %r90 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r89
    %r91 = load float, ptr %r90
    %r92 = mul i32 %r88,%r91
    %r93 = load float, ptr %r92
    %r94 = add i32 %r85,%r93
    %r96 = getelementptr [0 x void], ptr %r6, i32 0, i32 %r95
    store float %r94, ptr %r96
    %r98 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r97
    %r99 = load float, ptr %r98
    %r101 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r100
    %r102 = load float, ptr %r101
    %r103 = mul i32 %r99,%r102
    %r104 = load float, ptr %r103
    %r106 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r105
    %r107 = load float, ptr %r106
    %r109 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r108
    %r110 = load float, ptr %r109
    %r111 = mul i32 %r107,%r110
    %r112 = load float, ptr %r111
    %r113 = add i32 %r104,%r112
    %r114 = load float, ptr %r113
    %r116 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r115
    %r117 = load float, ptr %r116
    %r119 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r118
    %r120 = load float, ptr %r119
    %r121 = mul i32 %r117,%r120
    %r122 = load float, ptr %r121
    %r123 = add i32 %r114,%r122
    %r125 = getelementptr [0 x void], ptr %r7, i32 0, i32 %r124
    store float %r123, ptr %r125
    %r127 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r126
    %r128 = load float, ptr %r127
    %r130 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r129
    %r131 = load float, ptr %r130
    %r132 = mul i32 %r128,%r131
    %r133 = load float, ptr %r132
    %r135 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r134
    %r136 = load float, ptr %r135
    %r138 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r137
    %r139 = load float, ptr %r138
    %r140 = mul i32 %r136,%r139
    %r141 = load float, ptr %r140
    %r142 = add i32 %r133,%r141
    %r143 = load float, ptr %r142
    %r145 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r144
    %r146 = load float, ptr %r145
    %r148 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r147
    %r149 = load float, ptr %r148
    %r150 = mul i32 %r146,%r149
    %r151 = load float, ptr %r150
    %r152 = add i32 %r143,%r151
    %r154 = getelementptr [0 x void], ptr %r7, i32 0, i32 %r153
    store float %r152, ptr %r154
    %r156 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r155
    %r157 = load float, ptr %r156
    %r159 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r158
    %r160 = load float, ptr %r159
    %r161 = mul i32 %r157,%r160
    %r162 = load float, ptr %r161
    %r164 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r163
    %r165 = load float, ptr %r164
    %r167 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r166
    %r168 = load float, ptr %r167
    %r169 = mul i32 %r165,%r168
    %r170 = load float, ptr %r169
    %r171 = add i32 %r162,%r170
    %r172 = load float, ptr %r171
    %r174 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r173
    %r175 = load float, ptr %r174
    %r177 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r176
    %r178 = load float, ptr %r177
    %r179 = mul i32 %r175,%r178
    %r180 = load float, ptr %r179
    %r181 = add i32 %r172,%r180
    %r183 = getelementptr [0 x void], ptr %r7, i32 0, i32 %r182
    store float %r181, ptr %r183
    %r185 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r184
    %r186 = load float, ptr %r185
    %r188 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r187
    %r189 = load float, ptr %r188
    %r190 = mul i32 %r186,%r189
    %r191 = load float, ptr %r190
    %r193 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r192
    %r194 = load float, ptr %r193
    %r196 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r195
    %r197 = load float, ptr %r196
    %r198 = mul i32 %r194,%r197
    %r199 = load float, ptr %r198
    %r200 = add i32 %r191,%r199
    %r201 = load float, ptr %r200
    %r203 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r202
    %r204 = load float, ptr %r203
    %r206 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r205
    %r207 = load float, ptr %r206
    %r208 = mul i32 %r204,%r207
    %r209 = load float, ptr %r208
    %r210 = add i32 %r201,%r209
    %r212 = getelementptr [0 x void], ptr %r8, i32 0, i32 %r211
    store float %r210, ptr %r212
    %r214 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r213
    %r215 = load float, ptr %r214
    %r217 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r216
    %r218 = load float, ptr %r217
    %r219 = mul i32 %r215,%r218
    %r220 = load float, ptr %r219
    %r222 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r221
    %r223 = load float, ptr %r222
    %r225 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r224
    %r226 = load float, ptr %r225
    %r227 = mul i32 %r223,%r226
    %r228 = load float, ptr %r227
    %r229 = add i32 %r220,%r228
    %r230 = load float, ptr %r229
    %r232 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r231
    %r233 = load float, ptr %r232
    %r235 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r234
    %r236 = load float, ptr %r235
    %r237 = mul i32 %r233,%r236
    %r238 = load float, ptr %r237
    %r239 = add i32 %r230,%r238
    %r241 = getelementptr [0 x void], ptr %r8, i32 0, i32 %r240
    store float %r239, ptr %r241
    %r243 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r242
    %r244 = load float, ptr %r243
    %r246 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r245
    %r247 = load float, ptr %r246
    %r248 = mul i32 %r244,%r247
    %r249 = load float, ptr %r248
    %r251 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r250
    %r252 = load float, ptr %r251
    %r254 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r253
    %r255 = load float, ptr %r254
    %r256 = mul i32 %r252,%r255
    %r257 = load float, ptr %r256
    %r258 = add i32 %r249,%r257
    %r259 = load float, ptr %r258
    %r261 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r260
    %r262 = load float, ptr %r261
    %r264 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r263
    %r265 = load float, ptr %r264
    %r266 = mul i32 %r262,%r265
    %r267 = load float, ptr %r266
    %r268 = add i32 %r259,%r267
    %r270 = getelementptr [0 x void], ptr %r8, i32 0, i32 %r269
    store float %r268, ptr %r270
    ret i32 0
}
define i32 @main()
{
L1:  
    %r288 = load i32, ptr %r287
    %r289 = load i32, ptr @M
    %r290 = load i32, ptr %r289
    %r291 = icmp slt i32 %r288,%r290
    br i1 %r291, label %L1, label %L2
    %r288 = getelementptr [3 x void], ptr %r278, i32 0, i32 %r287
    store i32 %r287, ptr %r288
    %r288 = getelementptr [3 x void], ptr %r279, i32 0, i32 %r287
    store i32 %r287, ptr %r288
    %r288 = getelementptr [3 x void], ptr %r280, i32 0, i32 %r287
    store i32 %r287, ptr %r288
    %r288 = getelementptr [3 x void], ptr %r281, i32 0, i32 %r287
    store i32 %r287, ptr %r288
    %r288 = getelementptr [3 x void], ptr %r282, i32 0, i32 %r287
    store i32 %r287, ptr %r288
    %r288 = getelementptr [3 x void], ptr %r283, i32 0, i32 %r287
    store i32 %r287, ptr %r288
    %r288 = load i32, ptr %r287
    %r291 = add i32 %r288,%r289
    store i32 %r291, ptr %r287
    br label %L1
L2:  
L3:  
    %r288 = alloca i32
    %r287 = call i32 @mul(void %r278,void %r279,void %r280,void %r281,void %r282,void %r283,void %r284,void %r285,void %r286)
    store i32 %r287, ptr %r287
    br label %L3
    %r288 = load i32, ptr %r287
    %r289 = load i32, ptr @N
    %r290 = load i32, ptr %r289
    %r291 = icmp slt i32 %r288,%r290
    br i1 %r291, label %L4, label %L5
    %r288 = getelementptr [6 x void], ptr %r284, i32 0, i32 %r287
    store i32 %r288, ptr %r288
    %r289 = call i32 @putint(i32 %r288)
    %r288 = load i32, ptr %r287
    %r291 = add i32 %r288,%r289
    store i32 %r291, ptr %r287
    br label %L4
L4:  
L5:  
L6:  
    store i32 10, ptr %r288
    store i32 1, ptr %r287
    %r289 = call i32 @putch(i32 %r288)
    br label %L6
    %r288 = load i32, ptr %r287
    %r289 = load i32, ptr @N
    %r290 = load i32, ptr %r289
    %r291 = icmp slt i32 %r288,%r290
    br i1 %r291, label %L7, label %L8
    %r288 = getelementptr [3 x void], ptr %r285, i32 0, i32 %r287
    store i32 10, ptr %r288
    %r289 = call i32 @putint(i32 %r288)
    %r288 = load i32, ptr %r287
    %r291 = add i32 %r288,%r289
    store i32 %r291, ptr %r287
    br label %L7
L7:  
L8:  
L9:  
    store i32 10, ptr %r288
    store i32 1, ptr %r287
    %r289 = call i32 @putch(i32 %r288)
    br label %L9
    %r288 = load i32, ptr %r287
    %r289 = load i32, ptr @N
    %r290 = load i32, ptr %r289
    %r291 = icmp slt i32 %r288,%r290
    br i1 %r291, label %L10, label %L11
    %r288 = getelementptr [3 x void], ptr %r286, i32 0, i32 %r287
    store i32 10, ptr %r288
    %r289 = call i32 @putint(i32 %r288)
    %r288 = load i32, ptr %r287
    %r291 = add i32 %r288,%r289
    store i32 %r291, ptr %r287
    br label %L10
L10:  
L11:  
L12:  
    store i32 10, ptr %r288
    %r289 = call i32 @putch(i32 %r288)
    ret i32 0
}
