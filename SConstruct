build = ARGUMENTS.get('--build', 'coverage')

SConscript('SConscript_' + build,
  variant_dir='.build_' + build,
  duplicate=0,
  exports=[ 'build' ])
