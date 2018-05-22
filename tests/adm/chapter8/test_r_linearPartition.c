
// giving sequence:
// a b c d e f g
//
// construct two tables:
// \ a b c d e f g
// a 0 . .
// b   0 . .
// c     0 . .
// d       0 . .
// e         0 . .
// f           0 .
// g             0
//
// the bottom triangle does not hold any data;
//
// purpose of these two tables are to enable 
// fast look-up to decide the best partition
// strategy for a sequence [N, M] 
// for example the partition strategy for [c, f]
// can be retrieved by two look-ups:
//
// 1) the maximum difference between any two sub sequences
// 2) the boundary of the last sub sequence, 
//
// if the last sub sequence is [e, f] then the table 
// would record d at (f, c), hence [c, d] are remining 
// elements, whose optimal partition strategy can be 
// in turn retrieved from the table


