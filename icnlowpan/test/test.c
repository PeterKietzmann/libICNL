/*
 * Copyright (C) 2018 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "unity.h"
#include "icnlowpan.h"

#ifdef MODULE_NDNLOWPAN
#include "ndnlowpan.h"
#endif

static const uint8_t ndn_int[] = {
    0x05, 0x14, 0x07, 0x08, 0x08, 0x03, 0x48, 0x41,
    0x57, 0x08, 0x01, 0x41, 0x0a, 0x04, 0x12, 0x57,
    0x05, 0x00, 0x0c, 0x02, 0x0f, 0xa0
};

static const uint8_t ndn_int_disp[] = {
    0xF2, ICNL_DISPATCH_NDN_INT, /* Page 2 and LOWPAN_NDN_INT */
    0x05, 0x14, 0x07, 0x08, 0x08, 0x03, 0x48, 0x41,
    0x57, 0x08, 0x01, 0x41, 0x0a, 0x04, 0x12, 0x57,
    0x05, 0x00, 0x0c, 0x02, 0x0f, 0xa0
};

static const uint8_t ndn_int_hc_01[] = {
    0xF2, ICNL_DISPATCH_NDN_INT_HC_A, 0x44, /* Page 2 and LOWPAN_NDN_INT_HC_A */
    0x0E, 0x06, 0x03, 0x48, 0x41, 0x57, 0x01, 0x41,
    0x12, 0x57, 0x05, 0x00, 0x02, 0x0f, 0xa0
};

static const uint8_t ndn_data[] = {
    0x06, 0x18, 0x07, 0x08, 0x08, 0x03, 0x48, 0x41,
    0x57, 0x08, 0x01, 0x41, 0x14, 0x00, 0x15, 0x01,
    0x31, 0x16, 0x05, 0x1b, 0x01, 0x00, 0x1c, 0x00,
    0x17, 0x00
};

static const uint8_t ndn_data_disp[] = {
    0xF2, ICNL_DISPATCH_NDN_DATA, /* Page 2 and LOWPAN_NDN_DATA */
    0x06, 0x18, 0x07, 0x08, 0x08, 0x03, 0x48, 0x41,
    0x57, 0x08, 0x01, 0x41, 0x14, 0x00, 0x15, 0x01,
    0x31, 0x16, 0x05, 0x1b, 0x01, 0x00, 0x1c, 0x00,
    0x17, 0x00
};

static const uint8_t ndn_data_hc_01[] = {
    0xF2, ICNL_DISPATCH_NDN_DATA, /* Page 2 and LOWPAN_NDN_DATA */
    0x06, 0x18, 0x07, 0x08, 0x08, 0x03, 0x48, 0x41,
    0x57, 0x08, 0x01, 0x41, 0x14, 0x00, 0x15, 0x01,
    0x31, 0x16, 0x05, 0x1b, 0x01, 0x00, 0x1c, 0x00,
    0x17, 0x00
};
 
#ifdef MODULE_NDNLOWPAN
void test_encode_ndn(void)
{
    uint8_t out_int[sizeof(ndn_int) / sizeof(ndn_int[0]) + 2];
    uint8_t out_data[sizeof(ndn_data) / sizeof(ndn_data[0]) + 2];

    unsigned pos_int = icnl_encode(out_int, ICNL_PROTO_NDN, (uint8_t *)ndn_int,
                                   sizeof(ndn_int)/sizeof(ndn_int[0]));

    TEST_ASSERT_EQUAL_UINT(sizeof(ndn_int)/sizeof(ndn_int[0]) + 2, pos_int);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ndn_int, out_int + 2, pos_int - 2);

    unsigned pos_data = icnl_encode(out_data, ICNL_PROTO_NDN, (uint8_t *)ndn_data,
                                    sizeof(ndn_data)/sizeof(ndn_data[0]));

    TEST_ASSERT_EQUAL_UINT(sizeof(ndn_data)/sizeof(ndn_data[0]) + 2, pos_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ndn_data, out_data + 2, pos_data - 2);
}

void test_encode_ndn_hc_01(void)
{
    uint8_t out_int[sizeof(ndn_int) / sizeof(ndn_int[0]) + 2];

    unsigned pos_int = icnl_encode(out_int, ICNL_PROTO_NDN_HC, (uint8_t *)ndn_int,
                                   sizeof(ndn_int)/sizeof(ndn_int[0]));

    TEST_ASSERT_EQUAL_UINT(sizeof(ndn_int_hc_01)/sizeof(ndn_int_hc_01[0]), pos_int);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ndn_int_hc_01, out_int, pos_int);
}

void test_decode_ndn(void)
{
    uint8_t out_int[sizeof(ndn_int)/sizeof(ndn_int[0])];
    uint8_t out_data[sizeof(ndn_data)/sizeof(ndn_data[0])];

    unsigned pos_int = icnl_decode(out_int, (uint8_t *)ndn_int_disp,
                                   sizeof(ndn_int_disp)/sizeof(ndn_int_disp[0]));

    TEST_ASSERT_EQUAL_UINT(sizeof(ndn_int)/sizeof(ndn_int[0]), pos_int);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ndn_int, out_int, pos_int);

    unsigned pos_data = icnl_decode(out_data, (uint8_t *)ndn_data_disp,
                                    sizeof(ndn_data_disp)/sizeof(ndn_data_disp[0]));

    TEST_ASSERT_EQUAL_UINT(sizeof(ndn_data)/sizeof(ndn_data[0]), pos_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ndn_data, out_data, pos_data);
}

void test_decode_ndn_hc_01(void)
{
    uint8_t out_int[sizeof(ndn_int) / sizeof(ndn_int[0]) + 2];

    unsigned pos_int = icnl_decode(out_int, (uint8_t *)ndn_int_hc_01,
                                   sizeof(ndn_int_hc_01)/sizeof(ndn_int_hc_01[0]));

    TEST_ASSERT_EQUAL_UINT(sizeof(ndn_int)/sizeof(ndn_int[0]), pos_int);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ndn_int, out_int, pos_int);
}

#endif
 
int main(void)
{
    UNITY_BEGIN();
 
#ifdef MODULE_NDNLOWPAN
    RUN_TEST(test_encode_ndn);
    RUN_TEST(test_encode_ndn_hc_01);
    RUN_TEST(test_decode_ndn);
    RUN_TEST(test_decode_ndn_hc_01);
#endif
 
    return UNITY_END();
}
