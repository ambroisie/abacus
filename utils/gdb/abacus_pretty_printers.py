import gdb.printing

class BigNumPrinter(object):
    "Print a abacus::bignum::BigNum"

    def __init__(self, val):
        self.val = val

    def to_string(self):
        digits = self.val['digits_']
        begin, end = digits['_M_impl']['_M_start'], digits['_M_impl']['_M_finish']
        val = 0
        while begin != end:
            val *= 10
            val += begin.dereference()
            begin += 1
        val *= self.val['sign_']
        return str(val)

    def display_hint(self):
        return 'string'

def build_pretty_printer():
    pp = gdb.printing.RegexpCollectionPrettyPrinter('abacus')

    pp.add_printer('BigNum', '^abacus::bignum::BigNum$', BigNumPrinter)

    return pp

gdb.printing.register_pretty_printer(gdb.current_objfile(), build_pretty_printer(), True)
