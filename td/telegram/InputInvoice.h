//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2022
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/files/FileId.h"
#include "td/telegram/LabeledPricePart.h"
#include "td/telegram/MessageExtendedMedia.h"
#include "td/telegram/MessageId.h"
#include "td/telegram/Photo.h"
#include "td/telegram/td_api.h"
#include "td/telegram/telegram_api.h"

#include "td/utils/common.h"
#include "td/utils/Status.h"
#include "td/utils/StringBuilder.h"

namespace td {

class Td;

struct Invoice {
  string currency_;
  vector<LabeledPricePart> price_parts_;
  int64 max_tip_amount_ = 0;
  vector<int64> suggested_tip_amounts_;
  string recurring_payment_terms_of_service_url_;
  bool is_test_ = false;
  bool need_name_ = false;
  bool need_phone_number_ = false;
  bool need_email_address_ = false;
  bool need_shipping_address_ = false;
  bool send_phone_number_to_provider_ = false;
  bool send_email_address_to_provider_ = false;
  bool is_flexible_ = false;

  Invoice() = default;
  Invoice(string &&currency, bool is_test, bool need_shipping_address)
      : currency_(std::move(currency)), is_test_(is_test), need_shipping_address_(need_shipping_address) {
  }
};

struct InputInvoice {
  string title_;
  string description_;
  Photo photo_;
  string start_parameter_;
  Invoice invoice_;
  string payload_;
  string provider_token_;
  string provider_data_;
  MessageExtendedMedia extended_media_;

  int64 total_amount_ = 0;
  MessageId receipt_message_id_;

  InputInvoice() = default;

  InputInvoice(tl_object_ptr<telegram_api::messageMediaInvoice> &&message_invoice, Td *td, DialogId owner_dialog_id,
               FormattedText &&message);

  InputInvoice(tl_object_ptr<telegram_api::botInlineMessageMediaInvoice> &&message_invoice, Td *td,
               DialogId owner_dialog_id);

  static Result<InputInvoice> process_input_message_invoice(
      td_api::object_ptr<td_api::InputMessageContent> &&input_message_content, Td *td);

  tl_object_ptr<td_api::messageInvoice> get_message_invoice_object(Td *td, bool skip_bot_commands,
                                                                   int32 max_media_timestamp) const;

  tl_object_ptr<telegram_api::inputMediaInvoice> get_input_media_invoice(Td *td) const;

  tl_object_ptr<telegram_api::inputBotInlineMessageMediaInvoice> get_input_bot_inline_message_media_invoice(
      tl_object_ptr<telegram_api::ReplyMarkup> &&reply_markup, Td *td) const;

  vector<FileId> get_file_ids(const Td *td) const;

  void delete_thumbnail(Td *td);

  bool has_media_timestamp() const;

  const FormattedText *get_caption() const;

  int32 get_duration(const Td *td) const;

  FileId get_upload_file_id() const;

  FileId get_any_file_id() const;

  FileId get_thumbnail_file_id(const Td *td) const;

  bool update_extended_media(telegram_api::object_ptr<telegram_api::MessageExtendedMedia> extended_media,
                             DialogId owner_dialog_id, Td *td);
};

bool operator==(const InputInvoice &lhs, const InputInvoice &rhs);
bool operator!=(const InputInvoice &lhs, const InputInvoice &rhs);

tl_object_ptr<td_api::formattedText> get_product_description_object(const string &description);

}  // namespace td
