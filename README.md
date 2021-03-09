# 236379-LevenshteinBalls

This is a simulation to find the maximal levenshtein ball size for a given vector length n.
Here we iterate over a subset of {0,1}^n. The subset is determined as follows:
- We calculate the maximum of the set T(n) from the paper "On the Size of Levenshtein Balls", call it Tmax.
- We fix the first floor(n/Tmax) bits to be an alternating sequence
- The rest of the bits are iterated over from 00...0 to 11...1
For example, if n = 7 then Tmax is 2. Then, we fix the first 3 bits to be 101. Therefore, the fist word of the
iterated set is 1010000, and the last word is 1011111
This is a massive optimization compared to iterate over 2^n vectors, since we fix a large amount of bits.

The optimization is based on a few observations:
1. There is no difference (with respect to number of runs/alternating segments) between a vector and its opposite (1 turns to 0 and vice versa)
2. There is no difference (with respect to number of runs/alternating segments) between a vector and its reverse (1011 and 1101 for example)
3. From (2), if one sets vectors to begin with an alternating segment of a balanced length (ceil(n/t) / ceil(n/t)-1), The iterated set covers a vector equivalent to its reverse (with respect to number of runs) up to parity of n
4. It is known that vectors with a run of length > (n - floor(n/Tmax)) won't give a maximal levenshtein ball size, so skipping them will not miss potential vectors