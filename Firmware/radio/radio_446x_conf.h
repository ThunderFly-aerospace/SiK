/* see tools/build_si446x_table.py */
__code static const uint8_t shared_prop_ids[] = {
	0x03, 0x20, 0x00, 0x04, 0x20, 0x07, 0x01, 0x20, 0x18, 0x02, 0x20, 0x1a, 0x01, 0x20, 0x1d, 0x01, 0x20, 0x29, 0x01, 0x20, 0x35, 0x02, 0x20, 0x3b, 0x01, 0x20, 0x3f, 0x01, 0x20, 0x42, 0x01, 0x20, 0x44, 0x03, 0x20, 0x48, 0x01, 0x21, 0x0e, 0x01, 0x21, 0x20, 0x03, 0x22, 0x00, 0x01, 0x23, 0x02, 0x01, 0x23, 0x06, 0x00
};

__code static const uint8_t shared_prop_vals[] = {
	0x03, 0x00, 0x07, 0xc9, 0xc3, 0x80, 0x00, 0x01, 0x08, 0x03, 0x00, 0x02, 0xe2, 0x00, 0x1a, 0x00, 0xa4, 0xd6, 0x01, 0x80, 0xff, 0x15, 0x15, 0x08, 0x7f, 0x00, 0x0b, 0x03
};

__code static const uint8_t variable_prop_ids[] = {
	0x04, 0x20, 0x03, 0x02, 0x20, 0x0b, 0x01, 0x20, 0x19, 0x01, 0x20, 0x1c, 0x02, 0x20, 0x1e, 0x07, 0x20, 0x22, 0x01, 0x20, 0x2a, 0x07, 0x20, 0x2c, 0x03, 0x20, 0x38, 0x02, 0x20, 0x3d, 0x01, 0x20, 0x40, 0x01, 0x20, 0x43, 0x03, 0x20, 0x45, 0x0c, 0x21, 0x00, 0x02, 0x21, 0x0c, 0x0c, 0x21, 0x0f, 0x05, 0x21, 0x1b, 0x03, 0x21, 0x21, 0x01, 0x22, 0x03, 0x02, 0x23, 0x00, 0x03, 0x23, 0x03, 0x00
};

__code static const uint8_t band_433_prop_vals[13][75] = {
	{0x01, 0x38, 0x80, 0x05, 0x00, 0x83, 0x00, 0x80, 0x30, 0x10, 0x02, 0x71, 0x00, 0xd1, 0xb7, 0x00, 0x70, 0x00, 0x00, 0x12, 0x80, 0x11, 0x11, 0x2f, 0xa0, 0x11, 0x89, 0x89, 0x78, 0x00, 0x2b, 0x03, 0x03, 0x00, 0x3a, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x02, 0x71, 0x00, 0x05, 0x01, 0x06, 0x00, 0x80, 0x30, 0x20, 0x01, 0xd5, 0x01, 0x17, 0x9f, 0x00, 0x95, 0x00, 0x00, 0x12, 0x80, 0x23, 0x09, 0x09, 0xa0, 0x11, 0x67, 0x67, 0x78, 0x00, 0x2a, 0x03, 0x03, 0x00, 0x4d, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x04, 0xe2, 0x00, 0x05, 0x02, 0x38, 0x80, 0x80, 0x30, 0x20, 0x00, 0xea, 0x02, 0x2f, 0x3e, 0x01, 0x18, 0xc2, 0x04, 0x36, 0x80, 0x17, 0x0e, 0x0a, 0x80, 0x11, 0x33, 0x33, 0x82, 0x00, 0x29, 0x02, 0x83, 0x00, 0x8d, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x09, 0xc4, 0x00, 0x05, 0x04, 0x70, 0x80, 0x80, 0x20, 0x20, 0x00, 0xea, 0x02, 0x2f, 0x3e, 0x01, 0x18, 0xc2, 0x04, 0x36, 0x80, 0x2f, 0x09, 0xe2, 0x80, 0x11, 0x33, 0x33, 0x82, 0x00, 0x29, 0x02, 0x83, 0x00, 0x8d, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0b, 0x98, 0xc0, 0x05, 0x05, 0x1f, 0x00, 0x80, 0x20, 0x10, 0x00, 0x84, 0x03, 0xe4, 0x26, 0x01, 0xf7, 0x00, 0x00, 0x12, 0x80, 0xa6, 0x03, 0x29, 0xa0, 0x11, 0x1d, 0x1d, 0x7e, 0x51, 0x29, 0x03, 0x03, 0x01, 0x20, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0e, 0xa6, 0x00, 0x05, 0x06, 0x7c, 0x00, 0x80, 0x20, 0x10, 0x00, 0x68, 0x04, 0xea, 0x4b, 0x02, 0x7d, 0x00, 0x00, 0x12, 0x80, 0xd2, 0x02, 0xc5, 0xa0, 0x11, 0x17, 0x17, 0x7e, 0xab, 0x28, 0x03, 0x03, 0x01, 0x6c, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x09, 0xc4, 0x00, 0x09, 0x08, 0xb4, 0x00, 0x80, 0x20, 0x20, 0x00, 0x75, 0x04, 0x5e, 0x7b, 0x02, 0x32, 0x00, 0x00, 0x12, 0x81, 0x18, 0x02, 0xcc, 0xa0, 0x11, 0x1a, 0x1a, 0x7f, 0x80, 0x28, 0x03, 0x03, 0x01, 0x46, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0e, 0xa6, 0x00, 0x09, 0x0d, 0x24, 0x80, 0x80, 0x10, 0x20, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa4, 0xc2, 0x04, 0x36, 0x80, 0x8c, 0x06, 0x8d, 0x80, 0x11, 0x22, 0x22, 0x80, 0x55, 0x29, 0x02, 0x83, 0x00, 0xd0, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x13, 0x88, 0x00, 0x09, 0x11, 0x68, 0x00, 0x80, 0x10, 0x20, 0x00, 0x75, 0x04, 0x5e, 0x7b, 0x02, 0x32, 0x00, 0x00, 0x12, 0x82, 0x2f, 0x02, 0xc5, 0xa0, 0x11, 0x1a, 0x1a, 0x7f, 0x80, 0x28, 0x03, 0x03, 0x01, 0x46, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x1d, 0x4c, 0x00, 0x09, 0x1a, 0x48, 0x80, 0x80, 0x00, 0x10, 0x00, 0x68, 0x04, 0xea, 0x4b, 0x02, 0x76, 0xc2, 0x04, 0x36, 0x81, 0x18, 0x05, 0xec, 0x80, 0x11, 0x17, 0x17, 0x80, 0x55, 0x28, 0x02, 0x83, 0x01, 0x71, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x34, 0x04, 0x04, 0x07, 0x70},
	{0x27, 0x10, 0x00, 0x09, 0x22, 0xfd, 0x80, 0x80, 0x00, 0x20, 0x00, 0x75, 0x04, 0x5e, 0x7b, 0x02, 0x30, 0xc2, 0x04, 0x47, 0x82, 0xea, 0x02, 0xc2, 0x80, 0x11, 0x1a, 0x1a, 0x80, 0x20, 0x28, 0x02, 0x83, 0x01, 0x47, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x39, 0x04, 0x05, 0x04, 0x01},
	{0x3a, 0x98, 0x00, 0x09, 0x2b, 0x59, 0x00, 0x80, 0x00, 0x30, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xfc, 0x00, 0x00, 0x23, 0x8d, 0x1b, 0x01, 0x1e, 0xa0, 0x22, 0x11, 0x11, 0x69, 0xd5, 0x29, 0x03, 0x03, 0x00, 0xcb, 0x5b, 0x47, 0x0f, 0xc0, 0x6d, 0x25, 0xf4, 0xdb, 0xd6, 0xdf, 0xec, 0xf7, 0xfe, 0x01, 0xf0, 0xff, 0x03, 0x5b, 0x47, 0x0f, 0xc0, 0x6d, 0x25, 0xf4, 0xdb, 0xd6, 0xdf, 0xec, 0xf7, 0xfe, 0x01, 0xf0, 0xff, 0x03, 0x5d, 0x39, 0x04, 0x05, 0x04, 0x01},
	{0x26, 0x25, 0xa0, 0x01, 0x2b, 0x59, 0x00, 0x80, 0x00, 0x30, 0x00, 0x78, 0x04, 0x44, 0x44, 0x03, 0x5c, 0x00, 0x00, 0x23, 0x8f, 0xff, 0x00, 0xf6, 0xa0, 0x22, 0x0d, 0x0d, 0x51, 0x48, 0x28, 0x03, 0x03, 0x00, 0xcb, 0x7e, 0x64, 0x1b, 0xba, 0x58, 0x0b, 0xdd, 0xce, 0xd6, 0xe6, 0xf6, 0x00, 0x03, 0x03, 0xf0, 0x3f, 0x00, 0x7e, 0x64, 0x1b, 0xba, 0x58, 0x0b, 0xdd, 0xce, 0xd6, 0xe6, 0xf6, 0x00, 0x03, 0x03, 0xf0, 0x3f, 0x00, 0x5d, 0x01, 0x05, 0x05, 0x02, 0x00}
};

__code static const uint8_t band_868_prop_vals[13][75] = {
	{0x01, 0x38, 0x80, 0x05, 0x00, 0x42, 0x80, 0xc0, 0x20, 0x10, 0x04, 0xe2, 0x00, 0x68, 0xdc, 0x00, 0x34, 0xc2, 0x04, 0x36, 0x80, 0x03, 0x4c, 0x1f, 0x80, 0x11, 0xff, 0xff, 0x78, 0x00, 0x2b, 0x02, 0x83, 0x00, 0x1d, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x02, 0x71, 0x00, 0x05, 0x00, 0x83, 0x00, 0xc0, 0x20, 0x10, 0x02, 0x71, 0x00, 0xd1, 0xb7, 0x00, 0x70, 0x00, 0x00, 0x12, 0x80, 0x11, 0x11, 0x1d, 0xa0, 0x11, 0x89, 0x89, 0x78, 0x00, 0x2b, 0x03, 0x03, 0x00, 0x3a, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x04, 0xe2, 0x00, 0x05, 0x01, 0x1c, 0x80, 0xc0, 0x20, 0x20, 0x01, 0xd5, 0x01, 0x17, 0x9f, 0x00, 0x8c, 0xc2, 0x04, 0x36, 0x80, 0x0c, 0x15, 0xa8, 0x80, 0x11, 0x67, 0x67, 0x82, 0x00, 0x2a, 0x02, 0x83, 0x00, 0x46, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x09, 0xc4, 0x00, 0x05, 0x02, 0x38, 0x80, 0xc0, 0x20, 0x20, 0x00, 0xea, 0x02, 0x2f, 0x3e, 0x01, 0x18, 0xc2, 0x04, 0x36, 0x80, 0x17, 0x0d, 0xeb, 0x80, 0x11, 0x33, 0x33, 0x82, 0x00, 0x29, 0x02, 0x83, 0x00, 0x8d, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0b, 0x98, 0xc0, 0x05, 0x02, 0x8f, 0x00, 0xc0, 0x20, 0x20, 0x00, 0xc5, 0x02, 0x98, 0x19, 0x01, 0x51, 0x00, 0x00, 0x12, 0x80, 0x53, 0x04, 0xb8, 0xa0, 0x11, 0x2b, 0x2b, 0x7e, 0x51, 0x29, 0x03, 0x03, 0x00, 0xc0, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0e, 0xa6, 0x00, 0x05, 0x03, 0x3e, 0x00, 0xc0, 0x20, 0x20, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa9, 0x00, 0x00, 0x12, 0x80, 0x69, 0x04, 0x23, 0xa0, 0x11, 0x22, 0x22, 0x7e, 0xab, 0x29, 0x03, 0x03, 0x00, 0xf3, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x09, 0xc4, 0x00, 0x09, 0x04, 0x5a, 0x00, 0xc0, 0x10, 0x10, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa6, 0x00, 0x00, 0x12, 0x80, 0x8c, 0x03, 0x58, 0xa0, 0x11, 0x22, 0x22, 0x7f, 0x80, 0x29, 0x03, 0x03, 0x00, 0xf4, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0e, 0xa6, 0x00, 0x09, 0x06, 0x92, 0x80, 0xc0, 0x10, 0x20, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa4, 0xc2, 0x04, 0x36, 0x80, 0x46, 0x08, 0x1f, 0x80, 0x11, 0x22, 0x22, 0x80, 0x55, 0x29, 0x02, 0x83, 0x00, 0xd0, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x13, 0x88, 0x00, 0x09, 0x08, 0xb4, 0x00, 0xc0, 0x10, 0x20, 0x00, 0x75, 0x04, 0x5e, 0x7b, 0x02, 0x32, 0x00, 0x00, 0x12, 0x81, 0x18, 0x02, 0xc4, 0xa0, 0x11, 0x1a, 0x1a, 0x7f, 0x80, 0x28, 0x03, 0x03, 0x01, 0x46, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x1d, 0x4c, 0x00, 0x09, 0x0d, 0x24, 0x80, 0xc0, 0x00, 0x20, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa4, 0xc2, 0x04, 0x36, 0x80, 0x8c, 0x06, 0x63, 0x80, 0x11, 0x22, 0x22, 0x80, 0x55, 0x29, 0x02, 0x83, 0x00, 0xd0, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0x3d, 0x34, 0x04, 0x04, 0x07, 0x70},
	{0x27, 0x10, 0x00, 0x09, 0x11, 0x7e, 0x80, 0xc0, 0x00, 0x20, 0x00, 0x75, 0x04, 0x5e, 0x7b, 0x02, 0x30, 0xc2, 0x04, 0x47, 0x81, 0x75, 0x03, 0x10, 0x80, 0x11, 0x1a, 0x1a, 0x80, 0x20, 0x28, 0x02, 0x83, 0x01, 0x47, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x39, 0x04, 0x05, 0x04, 0x01},
	{0x3a, 0x98, 0x00, 0x09, 0x15, 0xad, 0x00, 0xc0, 0x00, 0x30, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xfc, 0x00, 0x00, 0x23, 0x86, 0x8e, 0x01, 0x1d, 0xa0, 0x22, 0x11, 0x11, 0x69, 0xd5, 0x29, 0x03, 0x03, 0x00, 0xcb, 0x5b, 0x47, 0x0f, 0xc0, 0x6d, 0x25, 0xf4, 0xdb, 0xd6, 0xdf, 0xec, 0xf7, 0xfe, 0x01, 0xf0, 0xff, 0x03, 0x5b, 0x47, 0x0f, 0xc0, 0x6d, 0x25, 0xf4, 0xdb, 0xd6, 0xdf, 0xec, 0xf7, 0xfe, 0x01, 0xf0, 0xff, 0x03, 0x5d, 0x39, 0x04, 0x05, 0x04, 0x01},
	{0x26, 0x25, 0xa0, 0x01, 0x15, 0xad, 0x00, 0xc0, 0x00, 0x30, 0x00, 0x78, 0x04, 0x44, 0x44, 0x03, 0x5c, 0x00, 0x00, 0x23, 0x88, 0x89, 0x00, 0xf3, 0xa0, 0x22, 0x0d, 0x0d, 0x51, 0x48, 0x28, 0x03, 0x03, 0x00, 0xcb, 0x7e, 0x64, 0x1b, 0xba, 0x58, 0x0b, 0xdd, 0xce, 0xd6, 0xe6, 0xf6, 0x00, 0x03, 0x03, 0xf0, 0x3f, 0x00, 0x7e, 0x64, 0x1b, 0xba, 0x58, 0x0b, 0xdd, 0xce, 0xd6, 0xe6, 0xf6, 0x00, 0x03, 0x03, 0xf0, 0x3f, 0x00, 0x5d, 0x01, 0x05, 0x05, 0x02, 0x00}
};

// FIXME! this is a copy of the 868 values for now
__code static const uint8_t band_915_prop_vals[13][75] = {
	{0x01, 0x38, 0x80, 0x05, 0x00, 0x42, 0x80, 0xc0, 0x20, 0x10, 0x04, 0xe2, 0x00, 0x68, 0xdc, 0x00, 0x34, 0xc2, 0x04, 0x36, 0x80, 0x03, 0x4c, 0x1f, 0x80, 0x11, 0xff, 0xff, 0x78, 0x00, 0x2b, 0x02, 0x83, 0x00, 0x1d, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x02, 0x71, 0x00, 0x05, 0x00, 0x83, 0x00, 0xc0, 0x20, 0x10, 0x02, 0x71, 0x00, 0xd1, 0xb7, 0x00, 0x70, 0x00, 0x00, 0x12, 0x80, 0x11, 0x11, 0x1d, 0xa0, 0x11, 0x89, 0x89, 0x78, 0x00, 0x2b, 0x03, 0x03, 0x00, 0x3a, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x04, 0xe2, 0x00, 0x05, 0x01, 0x1c, 0x80, 0xc0, 0x20, 0x20, 0x01, 0xd5, 0x01, 0x17, 0x9f, 0x00, 0x8c, 0xc2, 0x04, 0x36, 0x80, 0x0c, 0x15, 0xa8, 0x80, 0x11, 0x67, 0x67, 0x82, 0x00, 0x2a, 0x02, 0x83, 0x00, 0x46, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x09, 0xc4, 0x00, 0x05, 0x02, 0x38, 0x80, 0xc0, 0x20, 0x20, 0x00, 0xea, 0x02, 0x2f, 0x3e, 0x01, 0x18, 0xc2, 0x04, 0x36, 0x80, 0x17, 0x0d, 0xeb, 0x80, 0x11, 0x33, 0x33, 0x82, 0x00, 0x29, 0x02, 0x83, 0x00, 0x8d, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0b, 0x98, 0xc0, 0x05, 0x02, 0x8f, 0x00, 0xc0, 0x20, 0x20, 0x00, 0xc5, 0x02, 0x98, 0x19, 0x01, 0x51, 0x00, 0x00, 0x12, 0x80, 0x53, 0x04, 0xb8, 0xa0, 0x11, 0x2b, 0x2b, 0x7e, 0x51, 0x29, 0x03, 0x03, 0x00, 0xc0, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0e, 0xa6, 0x00, 0x05, 0x03, 0x3e, 0x00, 0xc0, 0x20, 0x20, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa9, 0x00, 0x00, 0x12, 0x80, 0x69, 0x04, 0x23, 0xa0, 0x11, 0x22, 0x22, 0x7e, 0xab, 0x29, 0x03, 0x03, 0x00, 0xf3, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x09, 0xc4, 0x00, 0x09, 0x04, 0x5a, 0x00, 0xc0, 0x10, 0x10, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa6, 0x00, 0x00, 0x12, 0x80, 0x8c, 0x03, 0x58, 0xa0, 0x11, 0x22, 0x22, 0x7f, 0x80, 0x29, 0x03, 0x03, 0x00, 0xf4, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0xcc, 0xa1, 0x30, 0xa0, 0x21, 0xd1, 0xb9, 0xc9, 0xea, 0x05, 0x12, 0x11, 0x0a, 0x04, 0xfc, 0x03, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x0e, 0xa6, 0x00, 0x09, 0x06, 0x92, 0x80, 0xc0, 0x10, 0x20, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa4, 0xc2, 0x04, 0x36, 0x80, 0x46, 0x08, 0x1f, 0x80, 0x11, 0x22, 0x22, 0x80, 0x55, 0x29, 0x02, 0x83, 0x00, 0xd0, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x13, 0x88, 0x00, 0x09, 0x08, 0xb4, 0x00, 0xc0, 0x10, 0x20, 0x00, 0x75, 0x04, 0x5e, 0x7b, 0x02, 0x32, 0x00, 0x00, 0x12, 0x81, 0x18, 0x02, 0xc4, 0xa0, 0x11, 0x1a, 0x1a, 0x7f, 0x80, 0x28, 0x03, 0x03, 0x01, 0x46, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0xff, 0xc4, 0x30, 0x7f, 0xf5, 0xb5, 0xb8, 0xde, 0x05, 0x17, 0x16, 0x0c, 0x03, 0x00, 0xff, 0x00, 0x00, 0x3d, 0x2c, 0x0e, 0x04, 0x0c, 0x73},
	{0x1d, 0x4c, 0x00, 0x09, 0x0d, 0x24, 0x80, 0xc0, 0x00, 0x20, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xa4, 0xc2, 0x04, 0x36, 0x80, 0x8c, 0x06, 0x63, 0x80, 0x11, 0x22, 0x22, 0x80, 0x55, 0x29, 0x02, 0x83, 0x00, 0xd0, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0xa2, 0x81, 0x26, 0xaf, 0x3f, 0xee, 0xc8, 0xc7, 0xdb, 0xf2, 0x02, 0x08, 0x07, 0x03, 0xfc, 0x0f, 0x00, 0x3d, 0x34, 0x04, 0x04, 0x07, 0x70},
	{0x27, 0x10, 0x00, 0x09, 0x11, 0x7e, 0x80, 0xc0, 0x00, 0x20, 0x00, 0x75, 0x04, 0x5e, 0x7b, 0x02, 0x30, 0xc2, 0x04, 0x47, 0x81, 0x75, 0x03, 0x10, 0x80, 0x11, 0x1a, 0x1a, 0x80, 0x20, 0x28, 0x02, 0x83, 0x01, 0x47, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0xff, 0xba, 0x0f, 0x51, 0xcf, 0xa9, 0xc9, 0xfc, 0x1b, 0x1e, 0x0f, 0x01, 0xfc, 0xfd, 0xff, 0x00, 0x0f, 0x3d, 0x39, 0x04, 0x05, 0x04, 0x01},
	{0x3a, 0x98, 0x00, 0x09, 0x15, 0xad, 0x00, 0xc0, 0x00, 0x30, 0x00, 0x9c, 0x03, 0x46, 0xdc, 0x01, 0xfc, 0x00, 0x00, 0x23, 0x86, 0x8e, 0x01, 0x1d, 0xa0, 0x22, 0x11, 0x11, 0x69, 0xd5, 0x29, 0x03, 0x03, 0x00, 0xcb, 0x5b, 0x47, 0x0f, 0xc0, 0x6d, 0x25, 0xf4, 0xdb, 0xd6, 0xdf, 0xec, 0xf7, 0xfe, 0x01, 0xf0, 0xff, 0x03, 0x5b, 0x47, 0x0f, 0xc0, 0x6d, 0x25, 0xf4, 0xdb, 0xd6, 0xdf, 0xec, 0xf7, 0xfe, 0x01, 0xf0, 0xff, 0x03, 0x5d, 0x39, 0x04, 0x05, 0x04, 0x01},
	{0x26, 0x25, 0xa0, 0x01, 0x15, 0xad, 0x00, 0xc0, 0x00, 0x30, 0x00, 0x78, 0x04, 0x44, 0x44, 0x03, 0x5c, 0x00, 0x00, 0x23, 0x88, 0x89, 0x00, 0xf3, 0xa0, 0x22, 0x0d, 0x0d, 0x51, 0x48, 0x28, 0x03, 0x03, 0x00, 0xcb, 0x7e, 0x64, 0x1b, 0xba, 0x58, 0x0b, 0xdd, 0xce, 0xd6, 0xe6, 0xf6, 0x00, 0x03, 0x03, 0xf0, 0x3f, 0x00, 0x7e, 0x64, 0x1b, 0xba, 0x58, 0x0b, 0xdd, 0xce, 0xd6, 0xe6, 0xf6, 0x00, 0x03, 0x03, 0xf0, 0x3f, 0x00, 0x5d, 0x01, 0x05, 0x05, 0x02, 0x00}
};

