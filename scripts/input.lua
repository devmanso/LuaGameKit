input = {}

input.mouse = {}

input.mouse.left = 0
input.mouse.right = 1
input.mouse.middle = 2
input.mouse.side = 3
input.mouse.extra = 4
input.mouse.forward = 5
input.mouse.back = 6


input.keyboard = {}
-- symbol keys
input.keyboard.none = 0 -- use for when no key is pressed
input.keyboard.apostrophe = 39 -- '
input.keyboard.comma = 44 -- ,
input.keyboard.minus = 45 -- -
input.keyboard.period = 46 -- .
input.keyboard.slash = 47 -- /
input.keyboard.semicolon = 59 -- ;
input.keyboard.equal = 61 -- =
input.keyboard.leftbracket = 91 -- [
input.keyboard.backslash = 92 -- \
input.keyboard.rightbracket = 93 -- ]
input.keyboard.backtick = 96 -- `

-- number keys
input.keyboard.zero = 48
input.keyboard.one = 49
input.keyboard.two = 50
input.keyboard.three = 51
input.keyboard.four = 52
input.keyboard.five = 53
input.keyboard.six = 54
input.keyboard.seven = 55
input.keyboard.eight = 56
input.keyboard.nine = 57

-- letters
input.keyboard.a = 65
input.keyboard.b = 66
input.keyboard.c = 67
input.keyboard.d = 68
input.keyboard.e = 69
input.keyboard.f = 70
input.keyboard.g = 71
input.keyboard.h = 72
input.keyboard.i = 73
input.keyboard.j = 74
input.keyboard.k = 75
input.keyboard.l = 76
input.keyboard.m = 77
input.keyboard.n = 78
input.keyboard.o = 79
input.keyboard.p = 80
input.keyboard.q = 81
input.keyboard.r = 82
input.keyboard.s = 83
input.keyboard.t = 84
input.keyboard.u = 85
input.keyboard.v = 86
input.keyboard.w = 87
input.keyboard.x = 88
input.keyboard.y = 89
input.keyboard.z = 90

-- function keys
input.keyboard.space = 32
input.keyboard.escape = 256
input.keyboard.enter = 257
input.keyboard.tab = 258
input.keyboard.backspace = 259
input.keyboard.insert = 260
input.keyboard.delete = 261
input.keyboard.rightarrow = 262
input.keyboard.leftarrow = 263
input.keyboard.downarrow = 264
input.keyboard.uparrow = 265
input.keyboard.pageup = 266
input.keyboard.pagedown = 267
input.keyboard.home = 268
 --[[ this can't be called 'end' because the Lua interpreter will think it's the end of something, 
input. and will throw an error]]
input.keyboard.endkey = 269
input.keyboard.capslock = 280
input.keyboard.scrolllock = 281
input.keyboard.numlock = 282
input.keyboard.printscreen = 283
input.keyboard.pause = 284

-- top row keys
input.keyboard.f1 = 290
input.keyboard.f2 = 291
input.keyboard.f3 = 292
input.keyboard.f4 = 293
input.keyboard.f5 = 294
input.keyboard.f6 = 295
input.keyboard.f7 = 296
input.keyboard.f8 = 297
input.keyboard.f9 = 298
input.keyboard.f10 = 299
input.keyboard.f11 = 300
input.keyboard.f12 = 301

-- bottom and side keys
input.keyboard.leftshift = 340
input.keyboard.leftcontrol = 341
input.keyboard.leftalt = 342
input.keyboard.leftsystemkey = 343 --[[ the system key or super key, is the command key on MacOS, 
input.or the Windows logo key on Windows]]
input.keyboard.rightshift = 344
input.keyboard.rightcontrol = 345
input.keyboard.rightalt = 346
input.keyboard.rightsystemkey = 347
input.keyboard.menu = 348

-- Keypad
input.keyboard.keypad = {}
input.keyboard.keypad.zero = 320
input.keyboard.keypad.one = 321
input.keyboard.keypad.two = 322
input.keyboard.keypad.three = 323
input.keyboard.keypad.four = 324
input.keyboard.keypad.five = 325
input.keyboard.keypad.six = 326
input.keyboard.keypad.seven = 327
input.keyboard.keypad.eight = 328
input.keyboard.keypad.nine = 329
input.keyboard.keypad.period = 330
input.keyboard.keypad.divide = 331
input.keyboard.keypad.multiply = 332
input.keyboard.keypad.subtract = 333
input.keyboard.keypad.add = 334
input.keyboard.keypad.enter = 335
input.keyboard.keypad.equal = 336

return input
