import re

_component_re = re.compile(r'(\d+ | \.)', re.VERBOSE)

#---------------------------------------------------------------------------------------------------
# Version class util
class Version:

    def __init__(self, s : str = None):
        if s:
            self.parse(s)

    def parse(self, s : str):
        parts : List[str] = [x for x in filter(lambda x: x and x != '.', _component_re.split(s))]

        self.components : List[int] = []

        for i in range(len(parts)):
            self.components.append(int(parts[i]))

    def __str__(self):
        return '.'.join([str(x) for x in self.components])

    def __unicode__(self):
        return '.'.join([str(x) for x in self.components])

    def __repr__(self):
        return '.'.join([str(x) for x in self.components])

    def __eq__(self, other):
        return Version.__cmp(self, other) == 0

    def __lt__(self, other):
        return Version.__cmp(self, other) < 0

    def __gt__(self, other):
        return Version.__cmp(self, other) > 0

    def __le__(self, other):
        return Version.__cmp(self, other) <= 0

    def __ge__(self, other):
        return Version.__cmp(self, other) >= 0

    @staticmethod
    def __cmp(lhs, rhs):
        i = 0
        while True:
            if i == len(lhs.components):
                if i == len(rhs.components):
                    return 0
                else:
                    return -1
            else:
                if i == len(rhs.components):
                    return 1
                elif lhs.components[i] != rhs.components[i]:
                    return lhs.components[i] - rhs.components[i]
            i = i + 1
