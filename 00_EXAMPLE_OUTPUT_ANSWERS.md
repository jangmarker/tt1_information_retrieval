# Example Output - As Required by Task

## schlag arm

```
> ./tt1_information_retrieval --db ../schlag schlag arm
Schlaganfall: 0.030081
Schlag (Torfabbau): 0.0212291
Stromschlag: 0.020097
Schlaghosen: 0.0119395
Schlag (Ort): 0.007827
Schlag (Wald): 0.00765374
Uhrschlag: 0.0075922
Peitsche (Schlagwaffe): 0.00677912
Schlag (Hunderassen): 0.00599551
Faustschlag: 0.00449149
Paddelschlag: 0.0035316
Schlagzahl (Kanusport): 0.00287267
Schlagzahl (Uhr): 0.00148627
Türbeschlag: 0.000467249
Blitzeinschlag: 0
Feldblock: 0
Kreuzschlag (Seile): 0
Reepschläger (Beruf): 0
Schlag (Takt): 0
Stoßgesetze: 0
Taubenschlag: 0
```

## schlag wasser
```
> ./tt1_information_retrieval --db ../schlag schlag wasser
Paddelschlag: 0.0738517
Schlag (Torfabbau): 0.02542
Schlaghosen: 0.0142966
Taubenschlag: 0.0130486
Schlag (Ort): 0.00937217
Schlag (Wald): 0.00916471
Uhrschlag: 0.00909102
Peitsche (Schlagwaffe): 0.00811742
Schlag (Hunderassen): 0.00717911
Blitzeinschlag: 0.00681612
Faustschlag: 0.00537818
Schlagzahl (Kanusport): 0.00343978
Stromschlag: 0.00343289
Schlagzahl (Uhr): 0.00177968
Türbeschlag: 0.000559491
Feldblock: 0
Kreuzschlag (Seile): 0
Reepschläger (Beruf): 0
Schlag (Takt): 0
Schlaganfall: 0
Stoßgesetze: 0
``` 

# More Examples

## schlag
```
> ./tt1_information_retrieval --db ../schlag schlag
Schlag (Torfabbau): 0.10623
Schlaghosen: 0.0597453
Schlag (Ort): 0.0391663
Schlag (Wald): 0.0382993
Uhrschlag: 0.0379913
Peitsche (Schlagwaffe): 0.0339227
Schlag (Hunderassen): 0.0300015
Faustschlag: 0.0224754
Paddelschlag: 0.0176721
Schlagzahl (Kanusport): 0.0143748
Stromschlag: 0.014346
Schlagzahl (Uhr): 0.0074373
Türbeschlag: 0.00233811
Blitzeinschlag: 0
Feldblock: 0
Kreuzschlag (Seile): 0
Reepschläger (Beruf): 0
Schlag (Takt): 0
Schlaganfall: 0
Stoßgesetze: 0
Taubenschlag: 0
```

## schlag wald
```
>. /tt1_information_retrieval --db ../schlag schlag wald
Feldblock: 0.0978652
Schlag (Torfabbau): 0.0165296
Schlaghosen: 0.00929645
Schlag (Ort): 0.00609432
Schlag (Wald): 0.00595942
Uhrschlag: 0.00591151
Peitsche (Schlagwaffe): 0.00527842
Schlag (Hunderassen): 0.00466827
Faustschlag: 0.0034972
Paddelschlag: 0.0027498
Schlagzahl (Kanusport): 0.00223674
Stromschlag: 0.00223226
Schlagzahl (Uhr): 0.00115725
Türbeschlag: 0.000363813
Blitzeinschlag: 0
Kreuzschlag (Seile): 0
Reepschläger (Beruf): 0
Schlag (Takt): 0
Schlaganfall: 0
Stoßgesetze: 0
Taubenschlag: 0
```

## wald
```
> ./tt1_information_retrieval --db ../schlag wald
Feldblock: 0.0990719
Blitzeinschlag: 0
Faustschlag: 0
Kreuzschlag (Seile): 0
Paddelschlag: 0
Peitsche (Schlagwaffe): 0
Reepschläger (Beruf): 0
Schlag (Hunderassen): 0
Schlag (Ort): 0
Schlag (Takt): 0
Schlag (Torfabbau): 0
Schlag (Wald): 0
Schlaganfall: 0
Schlaghosen: 0
Schlagzahl (Kanusport): 0
Schlagzahl (Uhr): 0
Stoßgesetze: 0
Stromschlag: 0
Taubenschlag: 0
Türbeschlag: 0
Uhrschlag: 0
```

# Advantages & Disadvantages

# Disadvantages

- Sole reliance on word forms leads to curious results, e.g. the search for
  "schlag" (example above) seems to indicate that "Blitzeinschlag.txt" doesn't
  contain "schlag" at all. "schlag" as a single word, is not in that
  file, however "Blitzeinschlag" is in it.

- The tokenization wasn't perfectly clearly defined in the task, which can lead to differing
  results: This implementation tokenizes "BDSM-Bereich" as "bdsmbereich", while it could also be
  tokenized as "bdsm" and "bereich". The second tokenization would increase the score of
  "Peitsche (Schlagwaffe)" when searched for "bdsm" compared to the first one.

- This implementation doesn't take document names (Wikipedia titles) into account.
  Looking at the query for "schlag wald" above one would expect "Schlag (Wald)" to appear
  before "Feldblock", because the former is closely related to "Wald" whereas the latter
  only remotely. Querying only for "wald" makes the issue even more apparent: "Schlag (Wald)"
  doesn't even match the query (score of 0).
  
# Advantages

- After the database is read in and the text-frequency-inverse-document-frequency matrix
  is calculated, queries take up a comparably small amount of work.

- The database can be reused for queries without modification (not in this implementation, but
  in principle), as long as the queried corpus isn't changed.

- Implementation of this method is straightforward, the algorithms don't require any lengthy
  training.

- Because no training is required it is rather easy to implement multiple different document
  similarity measures and compare them with each other (would require refactorings in this
  implementation).