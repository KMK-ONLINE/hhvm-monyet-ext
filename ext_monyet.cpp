#include "hphp/runtime/ext/extension.h"
#include "hphp/runtime/ext/array/ext_array.h"
#include "hphp/runtime/base/builtin-functions.h"
#include "hphp/runtime/base/collections.h"
#include "hphp/runtime/base/comparisons.h"
#include "hphp/runtime/base/container-functions.h"
#include "hphp/runtime/base/mixed-array.h"
#include "hphp/runtime/base/intercept.h"
#include "hphp/runtime/base/php-globals.h"
#include "hphp/runtime/base/hphp-system.h"
#include "hphp/runtime/ext/std/ext_std_errorfunc.h"
#include "hphp/runtime/ext/string/ext_string.h"
#include "hphp/util/logger.h"

#include <vector>

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

const StaticString
    s_compact("compact"),
    s_obs_compact("obs_compact"),
    s_my_compact("my_compact"),
    s_compact_sl("__SystemLib\\compact_sl"),
    s_my_compact_sl("my_compact_sl"),
    s_obs_compact_sl("obs_compact_sl"),
    s_comma(", "),
    s_squote("'"),
    s_file("file"),
    s_line("line");

static void dump_compact_arg(const Variant& var, Array& ary) {
  if (var.isArray()) {
    for (ArrayIter iter(var.getArrayData()); iter; ++iter) {
      dump_compact_arg(iter.second(), ary);
    }
  } else {
    String varname = s_squote + var.toString() + s_squote;
    ary.append( varname );
  }
}

String dump_compact(const Variant &varname, const Array& args)
{
  Array ary;

  dump_compact_arg(varname, ary);
  dump_compact_arg(args, ary);

  return HHVM_FN(implode)(s_comma, ary);
}

String dump_back_trace() {
  StringBuffer buf;
  Array bt = HHVM_FN(debug_backtrace)(k_DEBUG_BACKTRACE_PROVIDE_OBJECT, 1);

  for (ArrayIter it = bt.begin(); !it.end(); it.next()) {
    Array frame = it.second().toArray();

    if (frame.exists(s_file)) {
      buf.append(frame->get(s_file).toString());
      buf.append(':');
      buf.append(frame->get(s_line).toString());
    }
  }

  return buf.detach();
}

Array HHVM_FUNCTION(my_compact,
                    const Variant& varname,
                    const Array& args /* = null array */) {
  Array ret = HHVM_FN(compact)(varname, args);

  Logger::Info("compact(%s) in [%s]", dump_compact(varname, args).c_str(), dump_back_trace().c_str());

  return ret;
}

Array HHVM_FUNCTION(my_compact_sl,
                    const Variant& varname,
                    const Array& args /* = null array */) {
  Array ret = HHVM_FN(__SystemLib_compact_sl)(varname, args);

  Logger::Info("compact(%s) in [%s]", dump_compact(varname, args).c_str(), dump_back_trace().c_str());

  return ret;
}

void HHVM_FUNCTION(compact_intercept) {
    Logger::Info("compact intercepted!");
    rename_function(s_compact, s_obs_compact);
    rename_function(s_my_compact, s_compact);
    rename_function(s_compact_sl, s_obs_compact_sl);
    rename_function(s_my_compact_sl, s_compact_sl);
}

class MonyetExtension : public Extension {
 public:
  MonyetExtension(): Extension("monyet", "1.0") {}

  void moduleInit() override {

    HHVM_FE(compact_intercept);
    HHVM_FE(my_compact);
    HHVM_FE(my_compact_sl);

    loadSystemlib();
  }
} s_monyet_extension;

HHVM_GET_MODULE(monyet);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
