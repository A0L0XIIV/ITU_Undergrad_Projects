import Data.Char

data Color = Red | Black 
             deriving (Show, Eq)
data Suit = Clubs | Diamonds | Hearts | Spades
            deriving (Show, Eq)
data Rank = Num Int | Jack | Queen | King | Ace
            deriving (Show, Eq)
data Card = Card { suit :: Suit, rank :: Rank }
            deriving (Show, Eq)
data Move = Draw | Discard Card
            deriving Show
data State = Cont | Stop

type Goal = Int
type CardList = [Card]
type HeldCards = CardList

cardColor :: Card -> Color
cardColor (Card {suit = s, rank = _})
   | s == Hearts || s == Diamonds = Red
   | otherwise                    = Black
  
cardValue :: Card -> Int
cardValue (Card {suit = _, rank = r}) = case r of
   Num n -> n 
   Ace     -> 11
   _       -> 10
   
removeCard :: CardList -> Card -> CardList
removeCard [] _       = error "Not in deck"
removeCard (c':cs') c = if c' == c then cs' else c' : removeCard cs' c

sumCards :: CardList -> Int
sumCards cs = sumCards' 0 cs
   where
   sumCards' :: Int -> [Card] -> Int
   sumCards' acc []     = acc
   sumCards' acc (c:cs) = sumCards' (acc + cardValue c) cs

allSameColor :: [Card] -> Bool
allSameColor []        = True
allSameColor [x]       = True
allSameColor (x:y:xs)
   | cardColor x == cardColor y = allSameColor (y:xs)
   | otherwise                  = False

score :: [Card] -> Goal -> Int
score cs goal 
   | allSameColor cs = preliminary `div` 2
   | otherwise       = preliminary
      where
      sum = sumCards cs 
      preliminary
         | sum > goal = 3 * (sum - goal)
         | otherwise  = goal - sum    

runGame :: [Card] -> [Move] -> Goal -> Int
runGame cs ms g = runGame' [] cs ms
   where
      runGame' :: HeldCards -> [Card] -> [Move] -> Int
      runGame' hs cs []      = score hs g
      runGame' hs cs (m:ms') = case m of
         Discard c -> runGame' (removeCard hs c) cs ms'
         Draw      -> drawCard cs
            where
            drawCard :: CardList -> Int
            drawCard []     = score hs g
            drawCard (c:cs) 
               | sumCards hs' > g    = score hs' g
               | otherwise           = runGame' hs' cs ms'
                  where
                  hs' = (c:hs)
         
convertSuit :: Char -> Suit
convertSuit c
   | c `elem` "dD" = Diamonds
   | c `elem` "cC" = Clubs
   | c `elem` "hH" = Hearts
   | c `elem` "sS" = Spades
   | otherwise     = error "Unknown suit"
   
convertRank :: Char -> Rank
convertRank c
   | c `elem` "tT" = Num 10
   | c `elem` "jJ" = Jack
   | c `elem` "qQ" = Queen
   | c `elem` "kK" = King 
   | c == '1'      = Ace
   | isDigit c     = Num (digitToInt c)
   | otherwise     = error "Unknown rank"
   
convertCard :: (Char, Char) -> Card
convertCard (s, r) = Card (convertSuit s) (convertRank r)

convertMove :: (Char, Char, Char) -> Move
convertMove (m, s, r)
   | m `elem` "dD" = Draw
   | m `elem` "rR" = Discard (convertCard (s, r))
   | otherwise     = error "Unrecognized move"

readCards :: IO CardList
readCards = do line <- getLine
               if line == "."
                  then return []
                  else do rest <- readCards
                          return ((convertCard . validate) line : rest) where
                            validate :: String -> (Char, Char)
                            validate [c1,c2] = (c1, c2)
                            validate _       = error "Invalid string for card"

readMoves :: IO [Move]
readMoves = do line <- getLine
               if line == "."
                  then return []
                  else do rest <- readMoves
                          return ((convertMove . validate) line : rest) where
                            validate :: String -> (Char, Char, Char)
                            validate [c1]       = (c1, 'x', 'x')
                            validate [c1,c2,c3] = (c1, c2, c3)
                            validate _          = error "Invalid string for move"

main = do putStrLn "Enter cards:"
          cards <- readCards
          putStrLn "Enter moves:"
          moves <- readMoves
          putStrLn "Enter goal:"
          line <- getLine
          let goal = read line :: Int
          let score = runGame cards moves goal
          putStrLn ("Score: " ++ show score)   