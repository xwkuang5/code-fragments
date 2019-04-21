module Scrabble where

import Data.Monoid
import Data.Char

newtype Score = Score Int
  deriving (Eq, Ord, Show)

instance Monoid Score where
    mempty = Score 0
    mappend (Score a) (Score b) = Score (a + b)

score :: Char -> Score
score = scoreChar . toLower where
    scoreChar c
        | elem c "aeilnorstu" = Score  1
        | elem c "dg"         = Score  2
        | elem c "bcmp"       = Score  3
        | elem c "fhvwy"      = Score  4
        | elem c "k"          = Score  5
        | elem c "jx"         = Score  8
        | elem c "qz"         = Score 10
        | otherwise           = Score  0

scoreString :: String -> Score
scoreString = (foldr (<>) mempty) . (map score)

getScore :: Score -> Int
getScore (Score s) = s