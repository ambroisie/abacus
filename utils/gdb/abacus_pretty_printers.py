import gdb.printing

def digits_to_num(digits):
    res = 0
    for d in reversed(digits):
        res *= 10
        res += d
    return res

class BigNumPrinter(object):
    "Print a abacus::bignum::BigNum"

    def __init__(self, val):
        self.val = val

    def to_string(self):
        digits = self.val['digits_']
        begin, end = digits['_M_impl']['_M_start'], digits['_M_impl']['_M_finish']
        val = []
        while begin != end:
            val += [begin.dereference()]
            begin += 1
        val = digits_to_num(val)
        val *= self.val['sign_']
        return str(val)

    def display_hint(self):
        return 'string'

def build_pretty_printer():
    pp = gdb.printing.RegexpCollectionPrettyPrinter('abacus')

    pp.add_printer('BigNum', '^abacus::bignum::BigNum$', BigNumPrinter)

    return pp

gdb.printing.register_pretty_printer(gdb.current_objfile(), build_pretty_printer(), True)
