.name       "Batman"
.comment    "This city needs me"  # hello

loop: sti r1, %:live, %1

live:
        live %0
        ld %0, r2
        zjmp %:loop # hehehhehe

# hehehehhehehe

# 0b68 0100 0700 0101 0000 0000 0290 0000
# 0000 0209 ffed 
