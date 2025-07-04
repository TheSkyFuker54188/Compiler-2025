@ints = global [10000x i32] zeroinitializer
@intt = global i32 zeroinitializer
@chas = global [10000x i32] zeroinitializer
@chat = global i32 zeroinitializer
@i = global i32 0
@ii = global i32 1
@c = global i32 zeroinitializer
@get = global [10000x i32] zeroinitializer
@get2 = global [10000x i32] zeroinitializer
define i32 @isdigit(i32 %r0)
{
L1:  
    ret i32 1
    br label %L2
L3:  
    ret i32 0
}
define float @chapush(i32 %r0)
{
L1:  
    %r22 = load i32, ptr @chat
    %r23 = load i32, ptr %r22
    %r26 = add i32 %r23,%r24
    %r27 = load i32, ptr @chat
    store i32 %r26, ptr %r27
    %r22 = load i32, ptr @chat
    %r23 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r22
    store float %r21, ptr %r23
}
define i32 @power(i32 %r0,i32 %r11)
{
L1:  
    %r13 = alloca i32
    store i32 1, ptr %r13
    br label %L3
    %r13 = load i32, ptr %r12
    %r16 = icmp ne i32 %r13,%r14
    br i1 %r16, label %L4, label %L5
    %r14 = load i32, ptr %r13
    %r12 = load i32, ptr %r11
    %r13 = mul i32 %r14,%r12
    store i32 %r13, ptr %r13
    %r13 = load i32, ptr %r12
    %r16 = sub i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L4
L4:  
L5:  
L6:  
    ret i32 %r13
}
define i32 @getstr(i32 %r0)
{
L1:  
    %r17 = alloca i32
    %r15 = alloca i32
    %r16 = call i32 @getch()
    store i32 %r16, ptr %r15
    store i32 0, ptr %r17
    br label %L6
    %r16 = load i32, ptr %r15
    %r19 = icmp ne i32 %r16,%r17
    %r20 = load float, ptr %r19
    %r16 = load i32, ptr %r15
    %r19 = icmp ne i32 %r16,%r17
    %r20 = load float, ptr %r19
    %r21 = and i32 %r20,%r20
    br i1 %r21, label %L7, label %L8
    %r18 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r17
    store i32 %r15, ptr %r18
    %r21 = add i32 %r17,%r19
    store i32 %r21, ptr %r17
    %r18 = call i32 @getch()
    store i32 0, ptr %r15
    br label %L7
L7:  
L8:  
L9:  
    ret i32 13
}
define float @intpush(i32 %r0)
{
L1:  
    %r19 = load i32, ptr @intt
    %r20 = load i32, ptr %r19
    %r23 = add i32 %r20,%r21
    %r24 = load i32, ptr @intt
    store i32 %r23, ptr %r24
    %r19 = load i32, ptr @intt
    %r20 = getelementptr [10000 x i32], ptr @ints, i32 0, i32 %r19
    store float %r18, ptr %r20
}
define i32 @intpop()
{
L1:  
    %r24 = load i32, ptr @intt
    %r25 = load i32, ptr %r24
    %r28 = sub i32 %r25,%r26
    %r29 = load i32, ptr @intt
    store i32 %r28, ptr %r29
    %r30 = load i32, ptr @intt
    %r31 = load i32, ptr %r30
    %r34 = add i32 %r31,%r32
    %r35 = getelementptr [10000 x i32], ptr @ints, i32 0, i32 %r34
    ret i32 %r35
}
define i32 @chapop()
{
L1:  
    %r36 = load i32, ptr @chat
    %r37 = load i32, ptr %r36
    %r40 = sub i32 %r37,%r38
    %r41 = load i32, ptr @chat
    store i32 %r40, ptr %r41
    %r42 = load i32, ptr @chat
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    %r47 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r46
    ret i32 %r47
}
define float @intadd(i32 %r0)
{
L1:  
    %r49 = load i32, ptr @intt
    %r50 = getelementptr [10000 x i32], ptr @ints, i32 0, i32 %r49
    %r51 = load float, ptr %r50
    %r54 = mul i32 %r51,%r52
    %r55 = load i32, ptr @intt
    %r56 = getelementptr [10000 x i32], ptr @ints, i32 0, i32 %r55
    store float %r54, ptr %r56
    %r57 = load i32, ptr @intt
    %r58 = getelementptr [10000 x i32], ptr @ints, i32 0, i32 %r57
    %r59 = load float, ptr %r58
    %r49 = load i32, ptr %r48
    %r50 = add i32 %r59,%r49
    %r51 = load i32, ptr @intt
    %r52 = getelementptr [10000 x i32], ptr @ints, i32 0, i32 %r51
    store i32 %r50, ptr %r52
}
define i32 @find()
{
L1:  
    %r53 = call i32 @chapop()
    %r54 = load i32, ptr @c
    store i32 %r53, ptr %r54
    %r56 = load i32, ptr @ii
    %r57 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r56
    store i32 32, ptr %r57
    %r58 = load i32, ptr @c
    %r59 = load i32, ptr @ii
    %r60 = load i32, ptr %r59
    %r63 = add i32 %r60,%r61
    %r64 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r63
    store float %r58, ptr %r64
    %r65 = load i32, ptr @ii
    %r66 = load i32, ptr %r65
    %r69 = add i32 %r66,%r67
    %r70 = load i32, ptr @ii
    store i32 %r69, ptr %r70
    %r71 = load i32, ptr @chat
    %r72 = load i32, ptr %r71
    %r75 = icmp eq i32 %r72,%r73
    br i1 %r75, label %L9, label %L10
    ret i32 0
    br label %L11
L10:  
L12:  
    ret i32 1
}
define i32 @main()
{
L1:  
    %r82 = alloca i32
    %r79 = load i32, ptr @intt
    store i32 0, ptr %r79
    %r81 = load i32, ptr @chat
    store i32 0, ptr %r81
    %r15 = call i32 @getstr(i32 %r14)
    store i32 %r15, ptr %r82
    br label %L12
    %r16 = load i32, ptr @i
    %r17 = load i32, ptr %r16
    %r83 = load i32, ptr %r82
    %r84 = icmp slt i32 %r17,%r83
    br i1 %r84, label %L13, label %L14
    %r85 = load i32, ptr @i
    %r86 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r85
    %r87 = call i32 @isdigit(float %r86)
    %r88 = load float, ptr %r87
    %r91 = icmp eq i32 %r88,%r89
    br i1 %r91, label %L15, label %L16
    %r92 = load i32, ptr @i
    %r93 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r92
    %r94 = load i32, ptr @ii
    %r95 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r94
    store float %r93, ptr %r95
    %r96 = load i32, ptr @ii
    %r97 = load i32, ptr %r96
    %r100 = add i32 %r97,%r98
    %r101 = load i32, ptr @ii
    store i32 %r100, ptr %r101
    br label %L17
    %r102 = load i32, ptr @i
    %r103 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r102
    %r104 = load float, ptr %r103
    %r107 = icmp eq i32 %r104,%r105
    br i1 %r107, label %L18, label %L19
    %r109 = call i32 @chapush(i32 %r108)
    br label %L20
L13:  
L14:  
L15:  
    %r435 = alloca i32
    br label %L75
    %r430 = load i32, ptr @chat
    %r431 = load i32, ptr %r430
    %r434 = icmp sgt i32 %r431,%r432
    br i1 %r434, label %L76, label %L77
    %r436 = call i32 @chapop()
    store i32 %r436, ptr %r435
    %r438 = load i32, ptr @ii
    %r439 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r438
    store float 32, ptr %r439
    %r436 = load i32, ptr @ii
    %r437 = load i32, ptr %r436
    %r440 = add i32 %r437,%r438
    %r441 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r440
    store float %r435, ptr %r441
    %r442 = load i32, ptr @ii
    %r443 = load i32, ptr %r442
    %r446 = add i32 %r443,%r444
    %r447 = load i32, ptr @ii
    store i32 %r446, ptr %r447
    br label %L76
L16:  
L17:  
L18:  
    %r424 = load i32, ptr @i
    %r425 = load i32, ptr %r424
    %r428 = add i32 %r425,%r426
    %r429 = load i32, ptr @i
    store i32 %r428, ptr %r429
    br label %L13
L19:  
L21:  
    %r110 = load i32, ptr @i
    %r111 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r110
    %r112 = load float, ptr %r111
    %r115 = icmp eq i32 %r112,%r113
    br i1 %r115, label %L21, label %L22
    %r117 = call i32 @chapush(i32 %r116)
    br label %L23
L22:  
L24:  
    %r118 = load i32, ptr @i
    %r119 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r118
    %r120 = load float, ptr %r119
    %r123 = icmp eq i32 %r120,%r121
    br i1 %r123, label %L24, label %L25
    %r124 = call i32 @chapop()
    %r125 = load i32, ptr @c
    store i32 %r124, ptr %r125
    br label %L27
    %r126 = load i32, ptr @c
    %r127 = load i32, ptr %r126
    %r130 = icmp ne i32 %r127,%r128
    br i1 %r130, label %L28, label %L29
    %r132 = load i32, ptr @ii
    %r133 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r132
    store float 32, ptr %r133
    %r134 = load i32, ptr @c
    %r135 = load i32, ptr @ii
    %r136 = load i32, ptr %r135
    %r139 = add i32 %r136,%r137
    %r140 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r139
    store float %r134, ptr %r140
    %r141 = load i32, ptr @ii
    %r142 = load i32, ptr %r141
    %r145 = add i32 %r142,%r143
    %r146 = load i32, ptr @ii
    store i32 %r145, ptr %r146
    %r147 = call i32 @chapop()
    %r148 = load i32, ptr @c
    store i32 %r147, ptr %r148
    br label %L28
L25:  
L27:  
    %r149 = load i32, ptr @i
    %r150 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r149
    %r151 = load float, ptr %r150
    %r154 = icmp eq i32 %r151,%r152
    br i1 %r154, label %L30, label %L31
    br label %L33
    %r155 = load i32, ptr @chat
    %r156 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r155
    %r157 = load float, ptr %r156
    %r160 = icmp eq i32 %r157,%r158
    %r161 = load float, ptr %r160
    %r162 = load i32, ptr @chat
    %r163 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r162
    %r164 = load float, ptr %r163
    %r167 = icmp eq i32 %r164,%r165
    %r168 = load float, ptr %r167
    %r169 = xor i32 %r161,%r168
    %r170 = load float, ptr %r169
    %r171 = load i32, ptr @chat
    %r172 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r171
    %r173 = load float, ptr %r172
    %r176 = icmp eq i32 %r173,%r174
    %r177 = load float, ptr %r176
    %r178 = xor i32 %r170,%r177
    %r179 = load float, ptr %r178
    %r180 = load i32, ptr @chat
    %r181 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r180
    %r182 = load float, ptr %r181
    %r185 = icmp eq i32 %r182,%r183
    %r186 = load float, ptr %r185
    %r187 = xor i32 %r179,%r186
    %r188 = load float, ptr %r187
    %r189 = load i32, ptr @chat
    %r190 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r189
    %r191 = load float, ptr %r190
    %r194 = icmp eq i32 %r191,%r192
    %r195 = load float, ptr %r194
    %r196 = xor i32 %r188,%r195
    %r197 = load float, ptr %r196
    %r198 = load i32, ptr @chat
    %r199 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r198
    %r200 = load float, ptr %r199
    %r203 = icmp eq i32 %r200,%r201
    %r204 = load float, ptr %r203
    %r205 = xor i32 %r197,%r204
    br i1 %r205, label %L34, label %L35
    %r206 = call i32 @find()
    %r207 = load float, ptr %r206
    %r210 = icmp eq i32 %r207,%r208
    br i1 %r210, label %L36, label %L37
    br label %L35
    br label %L38
L28:  
L29:  
L30:  
    br label %L26
L31:  
L33:  
    %r213 = load i32, ptr @i
    %r214 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r213
    %r215 = load float, ptr %r214
    %r218 = icmp eq i32 %r215,%r216
    br i1 %r218, label %L39, label %L40
    br label %L42
    %r219 = load i32, ptr @chat
    %r220 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r219
    %r221 = load float, ptr %r220
    %r224 = icmp eq i32 %r221,%r222
    %r225 = load float, ptr %r224
    %r226 = load i32, ptr @chat
    %r227 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r226
    %r228 = load float, ptr %r227
    %r231 = icmp eq i32 %r228,%r229
    %r232 = load float, ptr %r231
    %r233 = xor i32 %r225,%r232
    %r234 = load float, ptr %r233
    %r235 = load i32, ptr @chat
    %r236 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r235
    %r237 = load float, ptr %r236
    %r240 = icmp eq i32 %r237,%r238
    %r241 = load float, ptr %r240
    %r242 = xor i32 %r234,%r241
    %r243 = load float, ptr %r242
    %r244 = load i32, ptr @chat
    %r245 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r244
    %r246 = load float, ptr %r245
    %r249 = icmp eq i32 %r246,%r247
    %r250 = load float, ptr %r249
    %r251 = xor i32 %r243,%r250
    %r252 = load float, ptr %r251
    %r253 = load i32, ptr @chat
    %r254 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r253
    %r255 = load float, ptr %r254
    %r258 = icmp eq i32 %r255,%r256
    %r259 = load float, ptr %r258
    %r260 = xor i32 %r252,%r259
    %r261 = load float, ptr %r260
    %r262 = load i32, ptr @chat
    %r263 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r262
    %r264 = load float, ptr %r263
    %r267 = icmp eq i32 %r264,%r265
    %r268 = load float, ptr %r267
    %r269 = xor i32 %r261,%r268
    br i1 %r269, label %L43, label %L44
    %r270 = call i32 @find()
    %r271 = load float, ptr %r270
    %r274 = icmp eq i32 %r271,%r272
    br i1 %r274, label %L45, label %L46
    br label %L44
    br label %L47
L34:  
L35:  
L36:  
    %r212 = call i32 @chapush(i32 %r211)
    br label %L32
L37:  
L39:  
    br label %L34
L40:  
L42:  
    %r277 = load i32, ptr @i
    %r278 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r277
    %r279 = load float, ptr %r278
    %r282 = icmp eq i32 %r279,%r280
    br i1 %r282, label %L48, label %L49
    br label %L51
    %r283 = load i32, ptr @chat
    %r284 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r283
    %r285 = load float, ptr %r284
    %r288 = icmp eq i32 %r285,%r286
    %r289 = load float, ptr %r288
    %r290 = load i32, ptr @chat
    %r291 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r290
    %r292 = load float, ptr %r291
    %r295 = icmp eq i32 %r292,%r293
    %r296 = load float, ptr %r295
    %r297 = xor i32 %r289,%r296
    %r298 = load float, ptr %r297
    %r299 = load i32, ptr @chat
    %r300 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r299
    %r301 = load float, ptr %r300
    %r304 = icmp eq i32 %r301,%r302
    %r305 = load float, ptr %r304
    %r306 = xor i32 %r298,%r305
    %r307 = load float, ptr %r306
    %r308 = load i32, ptr @chat
    %r309 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r308
    %r310 = load float, ptr %r309
    %r313 = icmp eq i32 %r310,%r311
    %r314 = load float, ptr %r313
    %r315 = xor i32 %r307,%r314
    br i1 %r315, label %L52, label %L53
    %r316 = call i32 @find()
    %r317 = load float, ptr %r316
    %r320 = icmp eq i32 %r317,%r318
    br i1 %r320, label %L54, label %L55
    br label %L53
    br label %L56
L43:  
L44:  
L45:  
    %r276 = call i32 @chapush(i32 %r275)
    br label %L41
L46:  
L48:  
    br label %L43
L49:  
L51:  
    %r323 = load i32, ptr @i
    %r324 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r323
    %r325 = load float, ptr %r324
    %r328 = icmp eq i32 %r325,%r326
    br i1 %r328, label %L57, label %L58
    br label %L60
    %r329 = load i32, ptr @chat
    %r330 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r329
    %r331 = load float, ptr %r330
    %r334 = icmp eq i32 %r331,%r332
    %r335 = load float, ptr %r334
    %r336 = load i32, ptr @chat
    %r337 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r336
    %r338 = load float, ptr %r337
    %r341 = icmp eq i32 %r338,%r339
    %r342 = load float, ptr %r341
    %r343 = xor i32 %r335,%r342
    %r344 = load float, ptr %r343
    %r345 = load i32, ptr @chat
    %r346 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r345
    %r347 = load float, ptr %r346
    %r350 = icmp eq i32 %r347,%r348
    %r351 = load float, ptr %r350
    %r352 = xor i32 %r344,%r351
    %r353 = load float, ptr %r352
    %r354 = load i32, ptr @chat
    %r355 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r354
    %r356 = load float, ptr %r355
    %r359 = icmp eq i32 %r356,%r357
    %r360 = load float, ptr %r359
    %r361 = xor i32 %r353,%r360
    br i1 %r361, label %L61, label %L62
    %r362 = call i32 @find()
    %r363 = load float, ptr %r362
    %r366 = icmp eq i32 %r363,%r364
    br i1 %r366, label %L63, label %L64
    br label %L62
    br label %L65
L52:  
L53:  
L54:  
    %r322 = call i32 @chapush(i32 %r321)
    br label %L50
L55:  
L57:  
    br label %L52
L58:  
L60:  
    %r369 = load i32, ptr @i
    %r370 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r369
    %r371 = load float, ptr %r370
    %r374 = icmp eq i32 %r371,%r372
    br i1 %r374, label %L66, label %L67
    br label %L69
    %r375 = load i32, ptr @chat
    %r376 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r375
    %r377 = load float, ptr %r376
    %r380 = icmp eq i32 %r377,%r378
    %r381 = load float, ptr %r380
    %r382 = load i32, ptr @chat
    %r383 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r382
    %r384 = load float, ptr %r383
    %r387 = icmp eq i32 %r384,%r385
    %r388 = load float, ptr %r387
    %r389 = xor i32 %r381,%r388
    %r390 = load float, ptr %r389
    %r391 = load i32, ptr @chat
    %r392 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r391
    %r393 = load float, ptr %r392
    %r396 = icmp eq i32 %r393,%r394
    %r397 = load float, ptr %r396
    %r398 = xor i32 %r390,%r397
    %r399 = load float, ptr %r398
    %r400 = load i32, ptr @chat
    %r401 = getelementptr [10000 x i32], ptr @chas, i32 0, i32 %r400
    %r402 = load float, ptr %r401
    %r405 = icmp eq i32 %r402,%r403
    %r406 = load float, ptr %r405
    %r407 = xor i32 %r399,%r406
    br i1 %r407, label %L70, label %L71
    %r408 = call i32 @find()
    %r409 = load float, ptr %r408
    %r412 = icmp eq i32 %r409,%r410
    br i1 %r412, label %L72, label %L73
    br label %L71
    br label %L74
L61:  
L62:  
L63:  
    %r368 = call i32 @chapush(i32 %r367)
    br label %L59
L64:  
L66:  
    br label %L61
L67:  
L69:  
    %r416 = load i32, ptr @ii
    %r417 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r416
    store float 32, ptr %r417
    %r418 = load i32, ptr @ii
    %r419 = load i32, ptr %r418
    %r422 = add i32 %r419,%r420
    %r423 = load i32, ptr @ii
    store i32 %r422, ptr %r423
    br label %L17
L70:  
L71:  
L72:  
    %r414 = call i32 @chapush(i32 %r413)
    br label %L68
L73:  
L75:  
    br label %L70
L76:  
L77:  
L78:  
    %r514 = alloca i32
    %r512 = alloca i32
    %r510 = alloca i32
    %r449 = load i32, ptr @ii
    %r450 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r449
    store float 64, ptr %r450
    %r452 = load i32, ptr @i
    store i32 1, ptr %r452
    br label %L78
    %r453 = load i32, ptr @i
    %r454 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r453
    %r455 = load float, ptr %r454
    %r458 = icmp ne i32 %r455,%r456
    br i1 %r458, label %L79, label %L80
    %r459 = load i32, ptr @i
    %r460 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r459
    %r461 = load float, ptr %r460
    %r464 = icmp eq i32 %r461,%r462
    %r465 = load float, ptr %r464
    %r466 = load i32, ptr @i
    %r467 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r466
    %r468 = load float, ptr %r467
    %r471 = icmp eq i32 %r468,%r469
    %r472 = load float, ptr %r471
    %r473 = xor i32 %r465,%r472
    %r474 = load float, ptr %r473
    %r475 = load i32, ptr @i
    %r476 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r475
    %r477 = load float, ptr %r476
    %r480 = icmp eq i32 %r477,%r478
    %r481 = load float, ptr %r480
    %r482 = xor i32 %r474,%r481
    %r483 = load float, ptr %r482
    %r484 = load i32, ptr @i
    %r485 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r484
    %r486 = load float, ptr %r485
    %r489 = icmp eq i32 %r486,%r487
    %r490 = load float, ptr %r489
    %r491 = xor i32 %r483,%r490
    %r492 = load float, ptr %r491
    %r493 = load i32, ptr @i
    %r494 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r493
    %r495 = load float, ptr %r494
    %r498 = icmp eq i32 %r495,%r496
    %r499 = load float, ptr %r498
    %r500 = xor i32 %r492,%r499
    %r501 = load float, ptr %r500
    %r502 = load i32, ptr @i
    %r503 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r502
    %r504 = load float, ptr %r503
    %r507 = icmp eq i32 %r504,%r505
    %r508 = load float, ptr %r507
    %r509 = xor i32 %r501,%r508
    br i1 %r509, label %L81, label %L82
    %r511 = call i32 @intpop()
    store i32 %r511, ptr %r510
    %r513 = call i32 @intpop()
    store i32 %r513, ptr %r512
    store i32 0, ptr %r514
    %r516 = load i32, ptr @i
    %r517 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r516
    %r518 = load float, ptr %r517
    %r521 = icmp eq i32 %r518,%r519
    br i1 %r521, label %L84, label %L85
    %r511 = load i32, ptr %r510
    %r513 = load i32, ptr %r512
    %r514 = add i32 %r511,%r513
    store i32 %r514, ptr %r514
    br label %L86
L79:  
L80:  
L81:  
    %r575 = getelementptr [10000 x i32], ptr @ints, i32 0, i32 %r574
    %r576 = call i32 @putint(float %r575)
    ret i32 0
L82:  
L83:  
L84:  
    %r568 = load i32, ptr @i
    %r569 = load i32, ptr %r568
    %r572 = add i32 %r569,%r570
    %r573 = load i32, ptr @i
    store i32 %r572, ptr %r573
    br label %L79
L85:  
L87:  
    %r515 = load i32, ptr @i
    %r516 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r515
    %r517 = load i32, ptr %r516
    %r520 = icmp eq i32 %r517,%r518
    br i1 %r520, label %L87, label %L88
    %r513 = load i32, ptr %r512
    %r511 = load i32, ptr %r510
    %r512 = sub i32 %r513,%r511
    store i32 %r512, ptr %r514
    br label %L89
L88:  
L90:  
    %r515 = load i32, ptr @i
    %r516 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r515
    %r517 = load i32, ptr %r516
    %r520 = icmp eq i32 %r517,%r518
    br i1 %r520, label %L90, label %L91
    %r511 = load i32, ptr %r510
    %r513 = load i32, ptr %r512
    %r514 = mul i32 %r511,%r513
    store i32 %r514, ptr %r514
    br label %L92
L91:  
L93:  
    %r515 = load i32, ptr @i
    %r516 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r515
    %r517 = load i32, ptr %r516
    %r520 = icmp eq i32 %r517,%r518
    br i1 %r520, label %L93, label %L94
    %r513 = load i32, ptr %r512
    %r511 = load i32, ptr %r510
    %r512 = sdiv i32 %r513,%r511
    store i32 %r512, ptr %r514
    br label %L95
L94:  
L96:  
    %r515 = load i32, ptr @i
    %r516 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r515
    %r517 = load i32, ptr %r516
    %r520 = icmp eq i32 %r517,%r518
    br i1 %r520, label %L96, label %L97
    %r513 = load i32, ptr %r512
    %r511 = load i32, ptr %r510
    %r512 = srem i32 %r513,%r511
    store i32 %r512, ptr %r514
    br label %L98
L97:  
L99:  
    %r515 = load i32, ptr @i
    %r516 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r515
    %r517 = load i32, ptr %r516
    %r520 = icmp eq i32 %r517,%r518
    br i1 %r520, label %L99, label %L100
    %r511 = call i32 @power(i32 %r512,i32 %r510)
    store i32 %r511, ptr %r514
    br label %L101
L100:  
L102:  
    %r515 = call i32 @intpush(i32 %r514)
    br label %L83
    %r516 = load i32, ptr @i
    %r517 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r516
    %r518 = load float, ptr %r517
    %r521 = icmp ne i32 %r518,%r519
    br i1 %r521, label %L102, label %L103
    %r522 = load i32, ptr @i
    %r523 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r522
    %r524 = load float, ptr %r523
    %r527 = sub i32 %r524,%r525
    %r528 = call i32 @intpush(float %r527)
    %r530 = load i32, ptr @ii
    store i32 1, ptr %r530
    br label %L105
    %r531 = load i32, ptr @i
    %r532 = load i32, ptr %r531
    %r533 = load i32, ptr @ii
    %r534 = load i32, ptr %r533
    %r535 = add i32 %r532,%r534
    %r536 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r535
    %r537 = load float, ptr %r536
    %r540 = icmp ne i32 %r537,%r538
    br i1 %r540, label %L106, label %L107
    %r541 = load i32, ptr @i
    %r542 = load i32, ptr %r541
    %r543 = load i32, ptr @ii
    %r544 = load i32, ptr %r543
    %r545 = add i32 %r542,%r544
    %r546 = getelementptr [10000 x i32], ptr @get2, i32 0, i32 %r545
    %r547 = load float, ptr %r546
    %r550 = sub i32 %r547,%r548
    %r551 = call i32 @intadd(float %r550)
    %r552 = load i32, ptr @ii
    %r553 = load i32, ptr %r552
    %r556 = add i32 %r553,%r554
    %r557 = load i32, ptr @ii
    store i32 %r556, ptr %r557
    br label %L106
L103:  
L105:  
    br label %L83
L106:  
L107:  
L108:  
    %r558 = load i32, ptr @i
    %r559 = load i32, ptr %r558
    %r560 = load i32, ptr @ii
    %r561 = load i32, ptr %r560
    %r562 = add i32 %r559,%r561
    %r563 = load float, ptr %r562
    %r566 = sub i32 %r563,%r564
    %r567 = load i32, ptr @i
    store i32 %r566, ptr %r567
    br label %L104
}
