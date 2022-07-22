host_build {
    QT_CPU_FEATURES.x86_64 = sse sse2
} else {
    QT_CPU_FEATURES.arm64 = 
}
QT.global_private.enabled_features = debug alloca_malloc_h alloca dbus gui network printsupport sql testlib widgets xml relocatable cross_compile largefile precompile_header simdAlways
QT.global_private.disabled_features = use_bfd_linker use_gold_linker use_lld_linker use_mold_linker android-style-assets gc_binaries developer-build no-prefix private_tests reduce_exports reduce_relocations sse2 sse3 ssse3 sse4_1 sse4_2 avx f16c avx2 avx512f avx512er avx512cd avx512pf avx512dq avx512bw avx512vl avx512ifma avx512vbmi aesni rdrnd rdseed shani mips_dsp mips_dspr2 neon arm_crc32 arm_crypto posix_fallocate alloca_h stack-protector-strong system-zlib zstd stdlib-libcpp dbus-linked libudev dlopen intelcet
CONFIG += cross_compile largefile precompile_header simdAlways
QT_COORD_TYPE = double
QT_BUILD_PARTS = libs

