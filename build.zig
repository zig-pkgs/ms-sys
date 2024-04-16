const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "ms-sys",
        .link_libc = true,
        .target = target,
        .optimize = optimize,
    });
    lib.defineCMacro("PACKAGE", "\"ms-sys\"");
    lib.defineCMacro("LOCALEDIR", "\"/usr/share/locale\"");
    lib.addIncludePath(b.path("upstream/inc"));
    lib.addCSourceFiles(.{
        .root = b.path("upstream"),
        .files = &ms_sys_src,
        .flags = &.{},
    });
    lib.addCSourceFile(.{
        .file = b.path("src/main.c"),
        .flags = &.{},
    });
    b.installArtifact(lib);

    const lib_unit_tests = b.addTest(.{
        .root_source_file = .{ .path = "src/root.zig" },
        .target = target,
        .optimize = optimize,
    });
    lib_unit_tests.linkLibrary(lib);

    const run_lib_unit_tests = b.addRunArtifact(lib_unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_lib_unit_tests.step);
}

const ms_sys_src = [_][]const u8{
    "src/partition_info.c",
    "src/br.c",
    "src/file.c",
    "src/ntfs.c",
    "src/fat16.c",
    "src/identify.c",
    "src/fat12.c",
    "src/exfat.c",
    "src/fat32.c",
    "src/oem_id.c",
    "src/nls.c",
    //"src/main.c",
};
