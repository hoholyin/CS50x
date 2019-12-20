import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        self.positivewords=set()
        """Initialize Analyzer."""
        file = open(positives, "r")
        for line in file:
            if line.startswith(';')==False:
                self.positivewords.add(line.rstrip("\n"))
            else:
                continue
        file.close()

        self.negativewords=set()
        file = open(negatives)
        for line in file:
            if line.startswith(';')==False:
                self.negativewords.add(line.rstrip("\n"))
            else:
                continue
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        text.lower()
        tokens=nltk.word_tokenize(text)
        score=0
        for token in tokens:
            if token in self.positivewords:
                score=score+1
            elif token in self.negativewords:
                score=score-1
            else:
                continue
        return score
