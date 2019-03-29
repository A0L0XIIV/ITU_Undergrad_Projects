data Color = Red | Black
data Suit = Clubs | Diamonds | Hearts | Spades
data Rank = Num Int | Jack | Queen | King | Ace
data Card = Card { suit :: Suit, rank :: Rank }
data Move = Draw | Discard Card

cardColor :: Card -> Color
  | Card Suit == Diamonds = Red
  | Card Suit == Hearts   = Red
  | Card Suit == Clubs    = Black
  | Card Suit == Spades   = Black
  
cardValue :: Card -> Rank
  | Card Rank == Num   = Num
  | Card Rank == Ace   = 11
  | otherwise          = 10
  
removeCard :: [Card] -> Card -> [Card]
removeCard [] _                   = []
removeCard (c:cs) crd | crd == c  = removeCard cs crd 
					  | otherwise = c : removeCard cs crd


allSameColor :: [Card] -> Bool
allSameColor []	       = True
allSameColor (c:cs)
  |c Color == head(cs) = allSameColor cs
  |otherwise           = False
  
  
sumCards :: [Card] -> Integer
sumCards sum 0 cs
  where
    sum Integer -> [Card] -> Integer
	sum total []   = total
	sum total c:cs = sum total+c cs


score :: [Card] -> Integer -> Integer
score [] _ 							 = error "Empty list"
score cs goal | sumCards(cs) == goal = 0
			  | sumCards(cs) > goal  = colorCheck 3 * (sumCards(cs) - goal) cs
			  | otherwise 	 		 = colorCheck goal - sumCards(cs) cs
			    where
				  colorCheck Integer -> [Card] -> Integer
				  colorCheck preSc cs'
				    | allSameColor cs = floor (fromIntegral (div preSc 2))
					| otherwise		  = preSc

--NOT FINISHED					
runGame :: [Card] -> [Move] -> Integer -> Integer
runGame (c:cL) (m:mL) goal
runGame _ [] _     				= score cL goal
runGame | m == Discard Card 		= discard (c:cL) mL
		| m == Draw && isEmpty(cL)    = y
          where
		    discard ...
	
	
convertSuit :: Char -> Suit
convertSuit c
  | c == 'd' || c == 'D' = Diamonds
  | c == 's' || c == 'S' = Spades
  | c == 'c' || c == 'C' = Clubs	
  | c == 'h' || c == 'H' = Hearts	
  | otherwise			 = error "Unknown suit"	
	

convertRank :: Char -> Rank
convertRank c
  | c == 'j' || c == 'J' 				   = Jack
  | c == 'q' || c == 'Q' 				   = Queen
  | c == 'k' || c == 'K' 				   = King
  | c == '1' || c == 'A' 				   = Ace
  | c == 't' || c == 'T'				   = 10
  | isDigit(c) && (1 < digitToInt(c) < 10) =  digitToInt(c)
  | otherwise							   = error "Unknown rank"
  
  
convertCard Char -> Char -> Card
convertCard st rk = Card(suit=st, rank=rk)


--readCards :: 

--NOT FINISHED
 
  