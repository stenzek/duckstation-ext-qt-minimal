QT_CPU_FEATURES.x86_64 = mmx sse sse2
QT.global_private.enabled_features = reduce_exports reduce_relocations sse2 sse3 ssse3 sse4_1 sse4_2 avx f16c avx2 avx512f avx512er avx512cd avx512pf avx512dq avx512bw avx512vl avx512ifma avx512vbmi aesni rdrnd rdseed shani posix_fallocate alloca_h alloca system-zlib dbus dbus-linked gui network printsupport sql testlib widgets xml dlopen relocatable force_debug_info headersclean largefile precompile_header enable_new_dtags sse2 sse3 ssse3 sse4_1 sse4_2 avx f16c avx2 avx512f avx512er avx512cd avx512pf avx512dq avx512bw avx512vl avx512ifma avx512vbmi aesni rdrnd rdseed shani simdAlways
QT.global_private.disabled_features = android-style-assets gc_binaries use_bfd_linker use_gold_linker use_lld_linker private_tests debug mips_dsp mips_dspr2 neon arm_crc32 arm_crypto alloca_malloc_h stack-protector-strong zstd libudev intelcet
CONFIG += force_debug_info headersclean largefile precompile_header enable_new_dtags sse2 sse3 ssse3 sse4_1 sse4_2 avx f16c avx2 avx512f avx512er avx512cd avx512pf avx512dq avx512bw avx512vl avx512ifma avx512vbmi aesni rdrnd rdseed shani simdAlways
PKG_CONFIG_EXECUTABLE = /usr/bin/pkg-config
QT_COORD_TYPE = double
QT_BUILD_PARTS = libs tools

QMAKE_LIBS_ZLIB = -lz
QMAKE_INCDIR_DBUS = /usr/lib64/dbus-1.0/include
QMAKE_LIBS_DBUS = -ldbus-1
