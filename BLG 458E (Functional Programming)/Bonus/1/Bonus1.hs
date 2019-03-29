dayOfWeek :: Integer -> Integer -> Integer -> Integer
dayOfWeek y m d
  | y == 0    = error "y cannot be zero"
  | m <= 0    = error "m should be positive & nonzero"
  | m > 12    = error "m cannot be bigger than 12"
  | d <= 0    = error "d should be positive & nonzero"
  | d > 31    = error "d cannot be bigger than 31"
  | otherwise = if m <= 2 then dayOfWeek y (m + 12) d else z
  where
    j :: Integer
    j  = div y 100
    k  = mod y 100
    t1 = floor (fromIntegral (13 * (m + 1)) / 5.0)
    t2 = floor (fromIntegral (div k 4))
    t3 = floor (fromIntegral (div j 4))
    z  = mod (d + t1 + k + t2 + t3 + 5 * j) 7


sundays1 :: Integer -> Integer -> Integer
sundays1 start end = sundays' start 1
  where
    rest = 0
    sundays' :: Integer -> Integer -> Integer
    sundays' y m
      | y > end   = rest
      | otherwise = if dayOfWeek y m 1 == 1 then rest + 1 else rest
      where
        nextY = if m < 12 then y else y + 1
        nextM = if m < 12 then m + 1 else 1
        rest = sundays' nextY nextM


leap :: Integer -> Bool
leap y = a
  where
    a = (mod y 4) == 0 && (mod y 100) /= 0 || (mod y 400) == 0


daysInMonth :: Integer -> Integer -> Integer
daysInMonth m y
  | m == 2    = if leap(y) then 29 else 28
  | m == 4    = 30
  | m == 6    = 30
  | m == 9    = 30
  | m == 11   = 30
  | otherwise = 31


sundays2 :: Integer -> Integer -> Integer
sundays2 start end = sundays' start 1
  where
    rest = 0
    sundays' :: Integer -> Integer -> Integer
    sundays' y m
      | y > end   = rest
      | otherwise = if (mod (daysInMonth m y) 7) == 0 then rest + 1 else rest
      where
        nextY = if m < 12 then y else y + 1
        nextM = if m < 12 then m + 1 else 1
        rest = sundays' nextY nextM












