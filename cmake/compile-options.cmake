target_compile_options(adizzle_adizzle INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -U_FORTIFY_SOURCE
        -D_FORTIFY_SOURCE=3
        -fstack-protector-strong
        -fcf-protection=full
        -fstack-clash-protection
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wcast-qual
        -Wformat=2
        -Wundef
        -Wfloat-equal
        -Wshadow
        -Wcast-align
        -Wunused
        -Wnull-dereference
        -Wdouble-promotion
        -Wimplicit-fallthrough
        -Wextra-semi
        -Woverloaded-virtual
        -Wnon-virtual-dtor
        -Wold-style-cast>
        
    $<$<CXX_COMPILER_ID:MSVC>:
        /sdl
        /guard:cf
        /utf-8
        /diagnostics:caret
        /w14165
        /w44242
        /w44254
        /w44263
        /w34265
        /w34287
        /w44296
        /w44365
        /w44388
        /w44464
        /w14545
        /w14546
        /w14547
        /w14549
        /w14555
        /w34619
        /w34640
        /w24826
        /w14905
        /w14906
        /w14928
        /w45038
        /W4
        /permissive-
        /volatile:iso
        /Zc:inline
        /Zc:preprocessor
        /Zc:enumTypes
        /Zc:lambda
        /Zc:__cplusplus
        /Zc:externConstexpr
        /Zc:throwingNew
        /EHsc>
)