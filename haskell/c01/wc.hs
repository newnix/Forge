-- c01/wc.hs
-- lines beginning with '--' are comments in haskell
-- This is a simple haskell word count program

main = interact wordCount
	where wordCount input = show (length (lines input)) ++ "\n"
