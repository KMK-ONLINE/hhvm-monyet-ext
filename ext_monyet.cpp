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
#include "hphp/runtime/ext/string/ext_string.h"
#include "hphp/util/logger.h"

#include <vector>

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

const StaticString
    s_compact("compact"),
    s_compact_sl("__SystemLib\\compact_sl"),
    s_obs_compact("obs_compact"),
    s_my_compact("my_compact");

static void my_compact(VarEnv* v, Array &ret, const Variant& var) {
  if (var.isArray()) {
    for (ArrayIter iter(var.getArrayData()); iter; ++iter) {
      my_compact(v, ret, iter.second());
    }
  } else {
    String varname = var.toString();
    Logger::Info("  '%s'", varname.c_str());
    if (!varname.empty() && v->lookup(varname.get()) != NULL) {
      ret.set(varname, *reinterpret_cast<Variant*>(v->lookup(varname.get())));
    }
  }
}

Array HHVM_FUNCTION(my_compact,
                    const Variant& varname,
                    const Array& args /* = null array */) {
  raise_disallowed_dynamic_call("compact should not be called dynamically");
  Logger::Info("my_compact(");
  Array ret = Array::attach(PackedArray::MakeReserve(args.size() + 1));
  VarEnv* v = g_context->getOrCreateVarEnv();
  if (v) {
    my_compact(v, ret, varname);
    my_compact(v, ret, args);
  }
  Logger::Info(")");
  return ret;
}

void HHVM_FUNCTION(compact_intercept) {
    Logger::Info("compact intercepted!");
    rename_function(s_compact_sl, s_obs_compact);
    rename_function(s_my_compact, s_compact_sl);
}

class MonyetExtension : public Extension {
 public:
  MonyetExtension(): Extension("monyet", "1.0") {}

  void moduleInit() override {

    HHVM_FE(compact_intercept);
    HHVM_FE(my_compact);

    loadSystemlib();
  }
} s_monyet_extension;

HHVM_GET_MODULE(monyet);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
