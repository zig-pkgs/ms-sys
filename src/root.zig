const std = @import("std");
const testing = std.testing;

pub extern fn ms_sys_main(c_argc: c_int, c_argv: [*][*:0]c_char) c_int;

test {}
